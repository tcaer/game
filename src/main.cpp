#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <bgfx/bgfx.h>
#include <toml++/toml.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "platform/platform.hpp"
#include "platform/glfwwindow.hpp"
#include "gfx/renderer.hpp"
#include "gfx/mesh/coloredcubemesh.hpp"
#include "world/camera.hpp"
#include "global.hpp"

Global global;

int main(void) {
    stbi_set_flip_vertically_on_load(true);
    
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

    Camera camera(60.0f, { 10, 5, 5 });

    int w, h, nrChannels;
    unsigned char* data = stbi_load("./res/textures/container.jpeg", &w, &h, &nrChannels, 0);
    const bgfx::Memory* im = bgfx::copy(data, w*h*nrChannels);

    bgfx::TextureHandle texture = bgfx::createTexture2D(w, h, false, 1, bgfx::TextureFormat::RGB8, BGFX_TEXTURE_NONE | BGFX_SAMPLER_NONE, im);
    stbi_image_free(data);

    bgfx::UniformHandle tex = bgfx::createUniform("texture", bgfx::UniformType::Sampler);

    unsigned counter = 0;
    while(!global.platform->window->is_close_requested()) {
        if (global.platform->window->resized()) {
            global.renderer->resize(global.platform->window->size());
        }

        global.platform->window->prepare_frame();
        global.renderer->prepare_frame();

        camera.update({ -10, 5, 5 });

        for (int x = 1; x < 21; x++) {
            for (int y = 1; y < 21; y++) {
                glm::mat4 mtx = glm::mat4(1.0);
                mtx = glm::translate(mtx, { 0, 0.5 * y, 0.5 * x});
                mtx = glm::rotate(mtx, counter * 0.01f, { x / 50, y / 50, 0.8 });
                mtx = glm::scale(mtx, { 0.15, 0.15, 0.15 });
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
                bgfx::setTexture(0, tex, texture);
                bgfx::submit(0, global.renderer->shader_manager.get_shader("cubes"));
            }
        }
        
        global.renderer->end_frame();
        counter++;
    }

    return 0;
}
