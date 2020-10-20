#include "Sprite.h"

#ifdef OPEN_GL_BUILD
#include <glad/glad.h>
#elif WEB_GL_BUILD
#define GL_GLEXT_PROTOTYPES 1
#include <SDL_opengles2.h>

#define glGenVertexArrays glGenVertexArraysOES
#define glBindVertexArray glBindVertexArrayOES
#define glDeleteVertexArrays glDeleteVertexArraysOES
#endif

Sprite::Sprite(): shader(nullptr), texture(nullptr)
{
}

Sprite::Sprite(Shader &shader, Texture2d& texture, Color color, Vector3 position, Vector3 scale, float rotation) :
    shader(shader), texture(texture), color(color), position(position), rotation(rotation), scale(scale)
{
    unsigned int VBO;
    //TODO make this 3d positions?
    float vertices[] = {
        //pos      //tex
        -0.5f,  0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f,  0.5f, 0.0f, 1.0f,
        0.5f,  0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Sprite::Sprite(Sprite&& other): shader(other.shader), texture(other.texture), quadVAO(other.quadVAO),
        color(other.color), position(other.position), scale(other.scale), rotation(other.rotation)
{
}

void Sprite::SetShaderData() const
{
    shader.Use();
    glActiveTexture(GL_TEXTURE0);
    texture.Bind();
    shader.SetVector4f("spriteColor", color.ToVec4());
}

Sprite::~Sprite()
{
    glDeleteVertexArrays(1, &this->quadVAO);
}
