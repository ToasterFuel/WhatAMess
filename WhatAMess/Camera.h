#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

#include "Math/Vector3.h"

class Camera
{
public:
    Vector3 position;
    float zoom;
    float nearClip;
    float farClip;

    Camera(Vector3 position, Vector3 rotation, float zoom, float nearClip, float farClip);
    glm::mat4 GetProjectionMatrix();
    glm::mat4 GetViewMatrix();
    void UpdateCameraVectors();

private:
    //TODO: when updating the rotation, make sure UpdateCameraVectors() is called
    //Euler angles in degrees
    Vector3 rotation;
    Vector3 front;
    Vector3 up;
    Vector3 right;
};
#endif