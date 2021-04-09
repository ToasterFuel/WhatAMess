#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

#include "../Math/Vector3.h"

class Camera
{
public:
    Vector3 position;
    float zoom;
    float nearClip;
    float farClip;

    Camera();
    void Init(Vector3 position, float rotation, float zoom, float nearClip, float farClip);
    /*
     * screenPosition should be in pixels with the origin in the top left
     */
    glm::vec2 ScreenToWorldPosition(glm::vec2 screenPosition);
    glm::mat4 GetProjectionMatrix() const;
    glm::mat4 GetViewMatrix();

    static Camera& Main()
    {
        static Camera main;
        return main;
    }

    float rotation;
};
#endif