#include <iostream>
#include <glm/glm.hpp>
#include <bgfx/bgfx.h>
#include <bx/math.h>
#include <toml++/toml.h>

#include "platform/platform.hpp"
#include "platform/glfwwindow.hpp"
#include "renderer/renderer.hpp"
#include "global.hpp"

Global global;

struct PosColorVertex
{
	float x;
	float y;
	float z;
	uint32_t abgr;
};

static PosColorVertex cubeVertices[] =
{
	{-1.0f,  1.0f,  1.0f, 0xff000000 },
	{ 1.0f,  1.0f,  1.0f, 0xff0000ff },
	{-1.0f, -1.0f,  1.0f, 0xff00ff00 },
	{ 1.0f, -1.0f,  1.0f, 0xff00ffff },
	{-1.0f,  1.0f, -1.0f, 0xffff0000 },
	{ 1.0f,  1.0f, -1.0f, 0xffff00ff },
	{-1.0f, -1.0f, -1.0f, 0xffffff00 },
	{ 1.0f, -1.0f, -1.0f, 0xffffffff },
};

static const uint16_t cubeTriList[] =
{
	0, 1, 2,
	1, 3, 2,
	4, 6, 5,
	5, 6, 7,
	0, 2, 4,
	4, 2, 6,
	1, 5, 3,
	5, 7, 3,
	0, 4, 1,
	4, 5, 1,
	2, 3, 6,
	6, 3, 7,
};

int main(void)
{
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

    bgfx::VertexLayout pcvDecl;
    pcvDecl.begin()
        .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
        .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
    .end();
    bgfx::VertexBufferHandle vbh = bgfx::createVertexBuffer(bgfx::makeRef(cubeVertices, sizeof(cubeVertices)), pcvDecl);
    bgfx::IndexBufferHandle ibh = bgfx::createIndexBuffer(bgfx::makeRef(cubeTriList, sizeof(cubeTriList)));

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
        
        bgfx::setVertexBuffer(0, vbh);
        bgfx::setIndexBuffer(ibh);
    
        bgfx::submit(0, global.renderer->shader_manager.get_shader("cubes"));
        
        global.renderer->end_frame();
        counter++;
    }

    bgfx::destroy(ibh);
    bgfx::destroy(vbh);

    return 0;
}
