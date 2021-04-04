#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"
#include "Window.h"

Camera::Camera(): position(Vector3()), rotation(0), zoom(1), nearClip(.1f), farClip(100.0f)
{
}

void Camera::Init(Vector3 position, float rotation, float zoom, float nearClip, float farClip)
{
    this->position = position;
    this->rotation = rotation;
    this->zoom = zoom;
    this->nearClip = nearClip;
    this->farClip = farClip;
}

glm::mat4 Camera::GetProjectionMatrix() const
{
    //glm::mat4 projection = glm::perspective(glm::radians(zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    float halfWidth = Window::Instance().GetWidth()/2 * zoom;
    float halfHeight = Window::Instance().GetHeight()/2 * zoom;
    return glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, nearClip, farClip);
}

glm::mat4 Camera::GetViewMatrix()
{
    glm::mat4 view(1.0f);
    view = glm::lookAt(position.ToGraphicsRepresentation(),
        (position + Vector3(0, 0, -1)).ToGraphicsRepresentation(),
        Vector3::UP.ToGraphicsRepresentation());
    view = glm::translate(view, glm::vec3(position.x, position.y, 0.0));
    view = glm::rotate(view, glm::radians(rotation), glm::vec3(0.0, 0.0, 1.0));
    view = glm::translate(view, glm::vec3(-position.x, -position.y, 0.0));

    return view;
}
