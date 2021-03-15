#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"
#include "Window.h"

Camera::Camera(): position(Vector3()), rotation(Vector3()), zoom(1), nearClip(.1f), farClip(100.0f)
{
    UpdateCameraVectors();
}

void Camera::Init(Vector3 position, Vector3 rotation, float zoom, float nearClip, float farClip)
{
    this->position = position;
    this->rotation = rotation;
    this->zoom = zoom;
    this->nearClip = nearClip;
    this->farClip = farClip;
    UpdateCameraVectors();
}

glm::mat4 Camera::GetProjectionMatrix() const
{
    //glm::mat4 projection = glm::perspective(glm::radians(zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    float halfWidth = Window::Instance().GetWidth() * zoom;
    float halfHeight = Window::Instance().GetHeight() * zoom;
    return glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, nearClip, farClip);
}

glm::mat4 Camera::GetViewMatrix() const
{
    return glm::lookAt(position.ToGraphicsRepresentation(),
        (position + front).ToGraphicsRepresentation(),
        up.ToGraphicsRepresentation());
}

void Camera::UpdateCameraVectors()
{
    front.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    front.y = sin(glm::radians(rotation.x));
    front.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    front = Vector3::Normalize(front);

    right = Vector3::Normalize(Vector3::Cross(front, Vector3::UP));
    up = Vector3::Normalize(Vector3::Cross(right, front));
}
