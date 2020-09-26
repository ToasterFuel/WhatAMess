#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"

Camera::Camera(Vector3 position, Vector3 up, float yaw, float pitch):
    front(Vector3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    this->position = position;
    worldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : front(Vector3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    position = Vector3(posX, posY, posZ);
    worldUp = Vector3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(position.ToGraphicsRepresentation(),
        (position + front).ToGraphicsRepresentation(),
        up.ToGraphicsRepresentation());
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    if(direction == FORWARD)
        position += up * velocity;
    if(direction == BACKWARD)
        position -= up * velocity;
    if(direction == LEFT)
        position -= right * velocity;
    if(direction == RIGHT)
        position += right * velocity;
}

void Camera::ProcessMouseScroll(float yoffset)
{
    Zoom -= (float)yoffset;
    if(Zoom < 1.0f)
        Zoom = 1.0f;
    if(Zoom > 45.0f)
        Zoom = 45.0f;
}

void Camera::updateCameraVectors()
{
    // calculate the new front vector
    Vector3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front = Vector3::Normalize(front);
    // also re-calculate the right and Up vector
    right = Vector3::Normalize(Vector3::Cross(front, worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    up = Vector3::Normalize(Vector3::Cross(right, front));
}
