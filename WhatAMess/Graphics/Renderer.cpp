#include "Renderer.h"
#include "../Utility/VectorUtils.h"

#ifdef OPEN_GL_BUILD
#include <glad/glad.h>
#elif WEB_GL_BUILD
#define GL_GLEXT_PROTOTYPES 1
#include <SDL_opengles2.h>
#define glBindVertexArray glBindVertexArrayOES
#endif
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void Renderer::SyncCameraViewProjection(Camera &camera)
{
    cameraView = camera.GetViewMatrix();
    cameraProjection = camera.GetProjectionMatrix();
}

void Renderer::DrawSprite(const Sprite &sprite) const
{
    sprite.SetShaderData();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, VectorUtils::ToVec3(sprite.position));
    //Translate to center before rotating??
    model = glm::rotate(model, glm::radians(sprite.rotation), glm::vec3(0, 0, 1));
    model = glm::scale(model, VectorUtils::ToVec3(sprite.scale));

    sprite.shader->SetMatrix4("model", model);
    sprite.shader->SetMatrix4("view", cameraView);
    sprite.shader->SetMatrix4("projection", cameraProjection);

    glBindVertexArray(sprite.quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    //glBindVertexArray(0);
}
