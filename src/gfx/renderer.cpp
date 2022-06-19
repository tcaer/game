#include "gfx/renderer.hpp"

#include "global.hpp"

Renderer::Renderer() = default;

Renderer::~Renderer() {
  bgfx::shutdown();
}

void Renderer::init(glm::vec2 window_size) {
  bgfx::PlatformData pd;
  global.platform->window->set_platform_data(pd);

  bgfx::Init bgfxInit;
  bgfxInit.platformData = pd;
  // BGFX can pick automatically but maybe allow user to choose?
  bgfxInit.type = bgfx::RendererType::Metal;
  bgfxInit.resolution.width = window_size.x;
  bgfxInit.resolution.height = window_size.y;
  bgfxInit.resolution.reset = BGFX_RESET_VSYNC;
  bgfx::renderFrame();
  bgfx::init(bgfxInit);

  bgfx::setViewRect(VIEW_MAIN, 0, 0, window_size.x, window_size.y);
  bgfx::setViewClear(VIEW_MAIN, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
  bgfx::setDebug(BGFX_DEBUG_TEXT | BGFX_DEBUG_STATS);

  shader_manager.init();
  texture_manager.init();
}

void Renderer::resize(glm::vec2 window_size) {
  bgfx::reset(window_size.x, window_size.y, BGFX_RESET_VSYNC);
  bgfx::setViewRect(VIEW_MAIN, 0, 0, window_size.x, window_size.y);
}

void Renderer::prepare_frame() {
  bgfx::touch(VIEW_MAIN);
  bgfx::dbgTextClear();

  bgfx::dbgTextPrintf(0, 0, 0xf, "BGFX is working!");
}

void Renderer::end_frame() {
  bgfx::frame();
}
