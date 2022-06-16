#include "world/camera.hpp"

#include <bgfx/bgfx.h>
#include <glm/ext.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "global.hpp"

Camera::Camera(float fov, glm::vec3 position) : m_position(position) {
    auto window_size = global.platform->window->size();
    m_projection = glm::perspective(glm::radians(fov),
                                    window_size.x / window_size.y,
                                    0.1f,
                                    100.0f);
}

void Camera::update(glm::vec3 lookAt) {
    glm::mat4 view = glm::mat4(1.0);
    view = glm::lookAt(lookAt,
                       m_position,
                       CAMERA_UP);
    bgfx::setViewTransform(0, glm::value_ptr(view), glm::value_ptr(m_projection));
}
