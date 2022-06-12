#include "renderer/renderer.hpp"

#include "global.hpp"

Renderer::Renderer() = default;

Renderer::~Renderer() {
  bgfx::shutdown();
}

void Renderer::init(unsigned width, unsigned height) {
  bgfx::PlatformData pd;
  global.platform->window->set_platform_data(pd);

  bgfx::Init bgfxInit;
  bgfxInit.platformData = pd;
  // BGFX can pick automatically but maybe allow user to choose?
  // bgfxInit.type = bgfx::RendererType::Metal;
  bgfxInit.resolution.width = width;
  bgfxInit.resolution.height = height;
  bgfxInit.resolution.reset = BGFX_RESET_VSYNC;
  bgfx::renderFrame();
  bgfx::init(bgfxInit);

  bgfx::setViewClear(VIEW_MAIN, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
  bgfx::setDebug(BGFX_DEBUG_TEXT | BGFX_DEBUG_STATS);
}

void Renderer::resize(unsigned width, unsigned height) {
  bgfx::reset(width, height, BGFX_RESET_VSYNC);
  bgfx::setViewRect(VIEW_MAIN, 0, 0, width, height);
}

void Renderer::prepare_frame() {
  bgfx::touch(VIEW_MAIN);
  bgfx::dbgTextClear();

  bgfx::dbgTextPrintf(0, 0, 0xf, "BGFX is working!");
}

void Renderer::end_frame() {
  bgfx::frame();
}