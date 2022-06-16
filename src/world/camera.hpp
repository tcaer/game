#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>

struct Camera {
    Camera(float fov, glm::vec3 position = { 0.0, 0.0, 0.0 });

    void update(glm::vec3 lookAt = { 0.0, 0.0, 0.0 });

private:
    glm::vec3 m_position;
    glm::mat4 m_projection;

    static constexpr glm::vec3 CAMERA_UP = { 0.0f, 0.0f, 1.0f };
};

#endif
