#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"

Camera::Camera(Vector3 position, Vector3 rotation, float zoom, float nearClip, float farClip):
        position(position), rotation(rotation), zoom(zoom), nearClip(nearClip), farClip(farClip)
{
    UpdateCameraVectors();
}

glm::mat4 Camera::GetProjectionMatrix()
{
    //glm::mat4 projection = glm::perspective(glm::radians(zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    float halfWidth = 800.0f / (2 * zoom);
    float halfHeight = 600.0f / (2 * zoom);
    return glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, nearClip, farClip);
}

glm::mat4 Camera::GetViewMatrix()
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
