#include <glm/gtc/matrix_transform.hpp>

#include "../Utility/VectorUtils.h"
#include "../Utility/MathUtils.h"
#include "Camera.h"
#include "Window.h"

Camera::Camera(): position(glm::vec3(0.0f, 0.0f, 0.0f)), rotation(0), zoom(1), nearClip(.1f), farClip(100.0f)
{
}

void Camera::Init(glm::vec3 position, float rotation, float zoom, float nearClip, float farClip)
{
    this->position = position;
    this->rotation = rotation;
    this->zoom = zoom;
    this->nearClip = nearClip;
    this->farClip = farClip;
}

glm::vec2 Camera::ScreenToWorldPosition(glm::vec2 screenPosition)
{
    screenPosition.x = MathUtils::Normalize(0, Window::Instance().GetWidth(), screenPosition.x) * 2 - 1;
    screenPosition.y = MathUtils::Normalize(0, Window::Instance().GetHeight(), screenPosition.y) * 2 - 1;
    screenPosition.x *= Window::Instance().GetWidth() * zoom / 2;
    screenPosition.y *= -1 * Window::Instance().GetHeight() * zoom / 2;

    glm::vec2 worldPosition;
    float rotation = glm::radians(-Camera::Main().rotation);
    worldPosition.x = screenPosition.x * glm::cos(rotation) - screenPosition.y * glm::sin(rotation);
    worldPosition.y = screenPosition.x * glm::sin(rotation) + screenPosition.y * glm::cos(rotation);

    worldPosition += glm::vec2(Camera::Main().position.x, Camera::Main().position.y);
    return worldPosition;
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
    view = glm::lookAt(position, position + VectorUtils::FORWARDv3, VectorUtils::UPv3);
    view = glm::translate(view, glm::vec3(position.x, position.y, 0.0));
    view = glm::rotate(view, glm::radians(rotation), glm::vec3(0.0, 0.0, 1.0));
    view = glm::translate(view, glm::vec3(-position.x, -position.y, 0.0));

    return view;
}
