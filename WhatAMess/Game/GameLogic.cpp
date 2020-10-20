#include "GameLogic.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Sprite.h"
#include "../Graphics/Texture2d.h"
#include "../Graphics/Renderer.h"
#include "../Input/Input.h"
#include "../Graphics/Window.h"
#include "../Timing/Time.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void processInput(Sprite &sprite);

Sprite* testSprite;
Sprite* testSprite2;
Texture2d* testTexture;
Shader* testShader;

GameLogic::GameLogic()
{
}

bool GameLogic::Init()
{
    Camera::Main().Init(Vector3(0, 0, 3), Vector3(0, -90, 0), 100, .1f, 100);
    testTexture = new Texture2d();

    int width, height, nrChannels;
    unsigned char *data = stbi_load("Assets/Textures/awesomeface.png", &width, &height, &nrChannels, 0);
    testTexture->Generate(width, height, nrChannels, data);
    stbi_image_free(data);

    ShaderData shaderData;
    if(!shaderData.LoadFromFile("Assets/Shaders/sprite.shader"))
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

    return true;
}

void GameLogic::Update()
{
    processInput(*testSprite);

    Renderer::Instance().SyncCameraViewProjection(Camera::Main());
    Renderer::Instance().DrawSprite(*testSprite);
    Renderer::Instance().DrawSprite(*testSprite2);
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
    sprite.position += moveDirection * 3 * Time::Instance().DeltaTime();

    float zoomMultiplier = 0;
    if(Input::IsKeyPressed(KEY_UP))
        zoomMultiplier += 1;
    if(Input::IsKeyPressed(KEY_DOWN))
        zoomMultiplier -= 1;

    float spinMultiplier = 0;
    if(Input::IsKeyPressed(KEY_RIGHT))
        spinMultiplier += 1;
    if(Input::IsKeyPressed(KEY_LEFT))
        spinMultiplier -= 1;

    sprite.rotation += spinMultiplier * 100 * Time::Instance().DeltaTime();
    Camera::Main().zoom += zoomMultiplier * 100 * Time::Instance().DeltaTime();
}
