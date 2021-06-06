#include "GameLogic.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Sprite.h"
#include "../Graphics/Texture2d.h"
#include "../Graphics/Renderer.h"
#include "../Input/Input.h"
#include "../Graphics/Window.h"
#include "../Timing/Time.h"
#include "../Utility/ResourceManager.h"
#include "../Utility/VectorUtils.h"
#include "Components/Ring.h"
#include "../Collision/AABBSystem.h"

#include <iostream>
#include <vector>

void processInput(Sprite &sprite);

Sprite* testSprite;
Sprite* testSprite2;
Sprite* background;
Texture2d* testTexture;
Texture2d* backgroundTexture;
Shader* testShader;

Shader* nineSliceShader;
Sprite* theBoxSprite;

Texture2d* ringTexture;
Texture2d* boxTexture;

std::vector<Ring*> ringHolder;

GameLogic::GameLogic()
{
}

bool GameLogic::Init()
{
    Camera::Main().Init(glm::vec3(0.0f, 0.0f, 3.0f), 0, 1, .1f, 100);
    testTexture = new Texture2d();

    int error = 0;
    ringTexture = new Texture2d();
    Image ringImage = ResourceManager::Instance().GetImage("Assets/Textures/Ring.png", &error);
    if(error != 0)
    {
        std::cout << "Failed to load ring image\n";
        return false;
    }
    ringTexture->Generate(ringImage);
    ResourceManager::Instance().FreeImage(ringImage);

    backgroundTexture = new Texture2d();
    Image backgroundImage = ResourceManager::Instance().GetImage("Assets/Textures/RoomBackground.png", &error);
    if(error != 0)
    {
        std::cout << "Failed to load background image\n";
        return false;
    }
    backgroundTexture->Generate(backgroundImage);
    ResourceManager::Instance().FreeImage(backgroundImage);

    Image faceImage = ResourceManager::Instance().GetImage("Assets/Textures/awesomeface.png", &error);
    if(error != 0)
    {
        std::cout << "Failed to load awesomeface image\n";
        return false;
    }
    testTexture->Generate(faceImage.width, faceImage.height, faceImage.bitsPerPixel, faceImage.data);
    ResourceManager::Instance().FreeImage(faceImage);

    ShaderData shaderData;
    if(!shaderData.LoadFromFile("Assets/Shaders/Sprite.shader"))
    {
        std::cout << "Failed to load shader.\n";
        return false;
    }
    testShader = new Shader();
    testShader->Compile(shaderData);
    testShader->SetVector4f("spriteColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    testSprite = new Sprite();
    testSprite->Init(testShader, testTexture);
    testSprite2 = new Sprite();
    testSprite2->Init(testShader, testTexture);
    testSprite2->position += glm::vec2(4.0f, -5.0f);
    background = new Sprite();
    background->Init(testShader, backgroundTexture);

    ShaderData nineSliceShaderData;
    if(!nineSliceShaderData.LoadFromFile("Assets/Shaders/NineSlice.shader"))
    {
        std::cout << "Failed to load shader.\n";
        return false;
    }

    //CreateRing(glm::vec2(0, 0));

    boxTexture = new Texture2d();
    Image boxImage = ResourceManager::Instance().GetImage("Assets/Textures/BoundingSquare.png", &error);
    if(error != 0)
    {
        std::cout << "Failed to load bounding square image\n";
        return false;
    }
    boxTexture->SetFilter(TEXTURE_NEAREST);
    boxTexture->Generate(boxImage);
    ResourceManager::Instance().FreeImage(boxImage);
    AABBSystem::Instance().Init(testShader, boxTexture);

    nineSliceShader = new Shader();
    nineSliceShader->Compile(nineSliceShaderData);
    nineSliceShader->SetVector4f("spriteColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    nineSliceShader->SetVector4f("borders", glm::vec4(0.33333f, 0.33333f, 0.66666f, 0.66666f));
    theBoxSprite = new Sprite();
    theBoxSprite->Init(nineSliceShader, boxTexture);

    return true;
}

float RandomFloat()
{
    float value = rand() % 100 / 100.0f;
    return value;
}

void GameLogic::CreateRing(glm::vec2 position)
{
    Ring* ring = new Ring();
    ring->Init(position, testShader, ringTexture);
    ringHolder.push_back(ring);
    AABBSystem::Instance().AddBoundingBox(ring->CreateBoundingBox());
}

void GameLogic::Update()
{
    processInput(*testSprite);

    Renderer::Instance().SyncCameraViewProjection(Camera::Main());
    //Renderer::Instance().DrawSprite(*background);
    //Renderer::Instance().DrawSprite(*testSprite);
    //Renderer::Instance().DrawSprite(*testSprite2);

    Renderer::Instance().DrawSprite(*theBoxSprite);

    for(Ring* ring: ringHolder)
    {
        ring->Render();
    }
    AABBSystem::Instance().RenderTree();

    if(Input::IsMouseButtonPressed(MOUSE_LEFT) && !prevButton)
    {
        glm::vec2 worldPosition = Camera::Main().ScreenToWorldPosition(Input::GetMouseScreenPosition());
        CreateRing(worldPosition);
    }

    prevButton = Input::IsMouseButtonPressed(MOUSE_LEFT);
}

void GameLogic::CleanUp()
{
}

void processInput(Sprite& sprite)
{
    if(Input::IsKeyPressed(KEY_ESCAPE))
        Window::Instance().Close();

    glm::vec2 scaleMultiplier = glm::vec2(0.0f, 0.0f);
    if(Input::IsKeyPressed(KEY_M))
        scaleMultiplier.x += 1;
    if(Input::IsKeyPressed(KEY_N))
        scaleMultiplier.x -= 1;
    if(Input::IsKeyPressed(KEY_C))
        scaleMultiplier.y += 1;
    if(Input::IsKeyPressed(KEY_V))
        scaleMultiplier.y -= 1;
    theBoxSprite->scale += scaleMultiplier * 100.0f * Time::Instance().DeltaTime();

    glm::vec2 moveDirection = glm::vec2(0.0f, 0.0f);
    if(Input::IsKeyPressed(KEY_W))
        moveDirection.y += 1;
    if(Input::IsKeyPressed(KEY_S))
        moveDirection.y -= 1;
    if(Input::IsKeyPressed(KEY_D))
        moveDirection.x += 1;
    if(Input::IsKeyPressed(KEY_A))
        moveDirection.x -= 1;

    glm::vec2 cameraMoveDirection = glm::vec2(0.0f, 0.0f);
    if(Input::IsKeyPressed(KEY_UP))
        cameraMoveDirection.y += 1;
    if(Input::IsKeyPressed(KEY_DOWN))
        cameraMoveDirection.y -= 1;
    if(Input::IsKeyPressed(KEY_LEFT))
        cameraMoveDirection.x -= 1;
    if(Input::IsKeyPressed(KEY_RIGHT))
        cameraMoveDirection.x += 1;

    float spinMultiplier = 0;
    if(Input::IsKeyPressed(KEY_K))
        spinMultiplier += 1;
    if(Input::IsKeyPressed(KEY_L))
        spinMultiplier -= 1;

    float zoomMultiplier = 0;
    if(Input::IsKeyPressed(KEY_I))
        zoomMultiplier += 1;
    if(Input::IsKeyPressed(KEY_O))
        zoomMultiplier -= 1;

    sprite.position += moveDirection * 300.0f * Time::Instance().DeltaTime();
    Camera& camera = Camera::Main();
    camera.rotation += spinMultiplier * 100 * Time::Instance().DeltaTime();
    camera.position += VectorUtils::ToVec3(cameraMoveDirection * 100.0f * Time::Instance().DeltaTime());
    camera.zoom += zoomMultiplier * Time::Instance().DeltaTime();
}
