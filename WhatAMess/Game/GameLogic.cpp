#include "GameLogic.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Sprite.h"
#include "../Graphics/Texture2d.h"
#include "../Graphics/Renderer.h"
#include "../Input/Input.h"
#include "../Graphics/Window.h"
#include "../Timing/Time.h"
#include "../Utility/ResourceManager.h"

#include <iostream>

void processInput(Sprite &sprite);

Sprite* testSprite;
Sprite* testSprite2;
Sprite* background;
Texture2d* testTexture;
Texture2d* backgroundTexture;
Shader* testShader;

GameLogic::GameLogic()
{
}

bool GameLogic::Init()
{
    Camera::Main().Init(Vector3(0, 0, 3), 0, 1, .1f, 100);
    testTexture = new Texture2d();

    backgroundTexture = new Texture2d();
    int error = 0;
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
    testSprite = new Sprite(*testShader, *testTexture);
    testSprite2 = new Sprite(*testShader, *testTexture);
    testSprite2->position += Vector3(4, -5);
    background = new Sprite(*testShader, *backgroundTexture);
    std::cout << "Initialized!!!\n";
    return true;
}

void GameLogic::Update()
{
    processInput(*testSprite);

    Renderer::Instance().SyncCameraViewProjection(Camera::Main());
    Renderer::Instance().DrawSprite(*background);
    Renderer::Instance().DrawSprite(*testSprite);
    Renderer::Instance().DrawSprite(*testSprite2);
    if(Input::IsMouseButtonPressed(MOUSE_LEFT))
    {
        glm::vec2 worldPosition = Camera::Main().ScreenToWorldPosition(Input::GetMouseScreenPosition());
        std::cout << "zoom: " << Camera::Main().zoom << " World: (" << worldPosition.x << ", " << worldPosition.y << ")\n";
    }
}

void GameLogic::CleanUp()
{
}

void processInput(Sprite& sprite)
{
    if(Input::IsKeyPressed(KEY_ESCAPE))
        Window::Instance().Close();

    Vector3 moveDirection = Vector3();
    if(Input::IsKeyPressed(KEY_W))
        moveDirection.y += 1;
    if(Input::IsKeyPressed(KEY_S))
        moveDirection.y -= 1;
    if(Input::IsKeyPressed(KEY_D))
        moveDirection.x += 1;
    if(Input::IsKeyPressed(KEY_A))
        moveDirection.x -= 1;

    Vector3 cameraMoveDirection = Vector3();
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

    sprite.position += moveDirection * 300 * Time::Instance().DeltaTime();
    Camera& camera = Camera::Main();
    camera.rotation += spinMultiplier * 100 * Time::Instance().DeltaTime();
    camera.position += cameraMoveDirection * 100 * Time::Instance().DeltaTime();
    camera.zoom += zoomMultiplier * Time::Instance().DeltaTime();
}
