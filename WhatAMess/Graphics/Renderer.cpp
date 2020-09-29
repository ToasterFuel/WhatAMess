#include "Renderer.h"

#include <glm/glm.hpp>

void Renderer::SyncCameraViewProjection(const Camera &camera)
{
    cameraView = camera.GetViewMatrix();
    cameraProjection = camera.GetProjectionMatrix();
}

void Renderer::DrawSprite(const Sprite &sprite) const
{
    sprite.shader.Use();

    glm::mat4 identity = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, sprite.position.ToGraphicsRepresentation());
    //Translate to center before rotating??
    model = glm::rotate(model, glm::radians(sprite.rotation), glm::vec3(0, 0, 1));
    model = glm::scale(model, sprite.scale.ToGraphicsRepresentation());

    sprite.shader.SetMatrix4("mvp", cameraProjection * cameraView * model);

    glActiveTexture(GL_TEXTURE0);
    sprite.texture.Bind();

    glBindVertexArray(sprite.quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
