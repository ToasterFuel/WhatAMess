/*
* TODO:
* 2a) Put vert/frag shader in the same file to read in
* 2b) Don't use glm for setting values in the shader

* 5) Create a time object that handles timing/delta timings
* 6) How do you want to handle global singletons like Timings/Window?
*/

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Input/Input.h"
#include "Utility/ShaderData.h"
#include "shader_s.h"
#include "Graphics/Camera.h"
#include "Graphics/Renderer.h"
#include "Graphics/Texture2d.h"
#include "Graphics/Window.h"
#include "Graphics/Sprite.h"
#include "Timing/Time.h"

#include <iostream>

void processInput(Camera &camera, Sprite &sprite);

int main()
{
    Camera camera(Vector3(0, 0, 3), Vector3(0, -90, 0), 100, .1f, 100);
    if (!Window::Instance().Init(800, 600, "What A Mess"))
    {
        Window::Instance().CleanUp();
        return -1;
    }

    Texture2d testTexture;
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("Assets/Textures/awesomeface.png", &width, &height, &nrChannels, 0);
    testTexture.Generate(width, height, nrChannels, data);
    stbi_image_free(data);

    Shader testShader;
    ShaderData shaderData;
    if(!shaderData.LoadFromFile("Assets/Shaders/sprite.shader"))
    {
        std::cout << "Failed to load shader.\n";
        return -1;
    }
    testShader.Compile(shaderData);
    testShader.SetVector4f("spriteColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    Sprite testSprite(testShader, testTexture);
    Sprite testSprite2(testShader, testTexture);
    testSprite2.position += Vector3(4, -5);

    while(Window::Instance().IsRunning())
    {
        Time::Instance().CalculateDeltaTime();
        processInput(camera, testSprite);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        Renderer::Instance().SyncCameraViewProjection(camera);
        Renderer::Instance().DrawSprite(testSprite);
        Renderer::Instance().DrawSprite(testSprite2);

        Window::Instance().SwapBuffers();
        Window::Instance().PullEvents();
    }

    Window::Instance().CleanUp();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(Camera &camera, Sprite& sprite)
{
    if (Input::IsKeyPressed(KEY_ESCAPE))
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
    camera.zoom += zoomMultiplier * 100 * Time::Instance().DeltaTime();
}
