#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <bgfx/bgfx.h>
#include <toml++/toml.h>

#include "platform/platform.hpp"
#include "platform/glfwwindow.hpp"
#include "gfx/renderer.hpp"
#include "gfx/mesh/coloredcubemesh.hpp"
#include "global.hpp"

Global global;

int main(void) {
    Platform platform;
    global.platform = &platform;

    try {
        global.settings = toml::parse_file("settings.toml");
    } catch (const toml::parse_error& err) {
        std::cerr << "Failed to parse settings.toml:\n" << err << std::endl;
        return 1;
    }

    platform.window = std::make_unique<GLFWWindow>(
        glm::vec2(
            global.settings["window"]["width"].value_or(1280),
            global.settings["window"]["height"].value_or(720)
        ),
        "Game"
    );

    Renderer renderer;
    global.renderer = &renderer;
    renderer.init(platform.window->size());
    renderer.resize(platform.window->size());

    ColoredCubeMesh mesh;
    mesh.load(nullptr);

    unsigned counter = 0;
    while(!global.platform->window->is_close_requested()) {
        if (global.platform->window->resized()) {
            global.renderer->resize(global.platform->window->size());
        }

        global.platform->window->prepare_frame();
        global.renderer->prepare_frame();

        glm::mat4 view = glm::mat4(1.0);
        view = glm::lookAt(glm::vec3(5.0f, 5.0f, 5.0f),
                           glm::vec3(0.0f, 0.0f, 0.0f),
                           glm::vec3(0.0f, 0.0f, 1.0f));

        glm::mat4 proj = glm::perspective(glm::radians(60.0f), 
                float(global.platform->window->size().x) / float(global.platform->window->size().y),
                0.1f,
                100.0f);
        bgfx::setViewTransform(0, glm::value_ptr(view), glm::value_ptr(proj));

        for (int x = 1; x < 21; x++) {
            for (int y = 1; y < 21; y++) {
                glm::mat4 mtx = glm::mat4(1.0);
                mtx = glm::translate(mtx, { 0, 0.4 * y, 0.2 * x});
                mtx = glm::rotate(mtx, counter * 0.01f, { x / 50, y / 50, 0.8 });
                mtx = glm::scale(mtx, { 0.2, 0.2, 0.2 });
                bgfx::setTransform(glm::value_ptr(mtx));
                mesh.bind();

                uint64_t  _state = 0
                    | BGFX_STATE_WRITE_RGB
                    | BGFX_STATE_WRITE_A
                    | BGFX_STATE_WRITE_Z
                    | BGFX_STATE_DEPTH_TEST_LESS
                    | BGFX_STATE_CULL_CCW
                    | BGFX_STATE_MSAA
                    ;
                bgfx::setState(_state);
                bgfx::submit(0, global.renderer->shader_manager.get_shader("cubes"));
            }
        }
        
        global.renderer->end_frame();
        counter++;
    }

    return 0;
}
