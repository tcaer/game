#include <iostream>
#include <glm/glm.hpp>
#include <bgfx/bgfx.h>
#include <bx/math.h>
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

        const bx::Vec3 at = {0.0f, 0.0f,  0.0f};
        const bx::Vec3 eye = {0.0f, 0.0f, -5.0f};
        float view[16];
        bx::mtxLookAt(view, eye, at);
        float proj[16];
        bx::mtxProj(proj, 60.0f, 
            float(global.platform->window->size().x) / float(global.platform->window->size().y), 
            0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
        bgfx::setViewTransform(0, view, proj);

        float mtx[16];
        bx::mtxRotateXY(mtx, counter * 0.01f, counter * 0.01f);
        bgfx::setTransform(mtx);
        
        mesh.bind();
    
        bgfx::submit(0, global.renderer->shader_manager.get_shader("cubes"));
        
        global.renderer->end_frame();
        counter++;
    }

    return 0;
}
