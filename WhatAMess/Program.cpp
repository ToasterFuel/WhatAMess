/*
* TODO:
* 2a) Put vert/frag shader in the same file to read in
* 2b) Don't use glm for setting values in the shader

* 3) Grab the Texture class from Breakout
* 4) Create some kind of renderer?
* 5) Create a time object that handles timing/delta timings
* 6) How do you want to handle global singletons like Timings/Window?
*/

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Input/Input.h"
#include "shader_s.h"
#include "Graphics/Camera.h"
#include "Graphics/Renderer.h"
#include "Graphics/Texture2d.h"
#include "Graphics/Window.h"
#include "Graphics/Sprite.h"

#include <iostream>

void processInput(Camera &camera, Sprite &sprite);

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
    Camera camera(Vector3(0, 0, 3), Vector3(0, -90, 0), 100, .1f, 100);
    if (!Window::Instance().Init(800, 600, "What A Mess"))
    {
        Window::Instance().CleanUp();
        return -1;
    }

    // build and compile our shader zprogram
    // ------------------------------------
    Shader_s ourShader("Assets/Shaders/texture.vs", "Assets/Shaders/texture.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // load and create a texture 
    // -------------------------
    unsigned int texture1, texture2;
    // texture 1
    // ---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
                                            // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data = stbi_load("Assets/Textures/container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    // texture 2
    // ---------
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    data = stbi_load("Assets/Textures/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);









    Texture2d testTexture;
    data = stbi_load("Assets/Textures/awesomeface.png", &width, &height, &nrChannels, 0);
    testTexture.Generate(width, height, nrChannels, data);
    stbi_image_free(data);

    Shader testShader;
    std::string vertexCode;
    std::string fragmentCode;
    try
    {
        // open files
        std::ifstream vertexShaderFile("Assets/Shaders/sprite.vs");
        std::ifstream fragmentShaderFile("Assets/Shaders/sprite.frag");
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();
    testShader.Compile(vShaderCode, fShaderCode);
    Sprite testSprite(testShader, testTexture);
    Sprite testSprite2(testShader, testTexture);
    testSprite2.position += Vector3(4, -5);





    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use(); // don't forget to activate/use the shader before setting uniforms!
                     // either set it manually like so:
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
    // or set it via the texture class
    ourShader.setInt("texture2", 1);

    // render loop
    // -----------
    while (Window::Instance().IsRunning())
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(camera, testSprite);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        Renderer::Instance().SyncCameraViewProjection(camera);
        Renderer::Instance().DrawSprite(testSprite);
        Renderer::Instance().DrawSprite(testSprite2);

        /*
        ourShader.use();
        glm::mat4 identity = glm::mat4(1.0f);
        ourShader.setMat4("model", identity);
        ourShader.setMat4("view", identity);
        glm::mat4 projection = camera.GetProjectionMatrix() * camera.GetViewMatrix();
        ourShader.setMat4("projection", projection);
        ourShader.setVec3("aColor", glm::vec3(1, 1, 1));
        // render
        // ------
        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        // render container
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        */
        Window::Instance().SwapBuffers();
        Window::Instance().PullEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

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
    if (Input::IsKeyPressed(KEY_W))
        moveDirection.y += 1;
    if (Input::IsKeyPressed(KEY_S))
        moveDirection.y -= 1;
    if (Input::IsKeyPressed(KEY_D))
        moveDirection.x += 1;
    if (Input::IsKeyPressed(KEY_A))
        moveDirection.x -= 1;
    sprite.position += moveDirection * 3 * deltaTime;

    float zoomMultiplier = 0;
    if (Input::IsKeyPressed(KEY_UP))
        zoomMultiplier += 1;
    if (Input::IsKeyPressed(KEY_DOWN))
        zoomMultiplier -= 1;

    float spinMultiplier = 0;
    if (Input::IsKeyPressed(KEY_RIGHT))
        spinMultiplier += 1;
    if (Input::IsKeyPressed(KEY_LEFT))
        spinMultiplier -= 1;

    sprite.rotation += spinMultiplier * 100 * deltaTime;
    camera.zoom += zoomMultiplier * 100 * deltaTime;
}
