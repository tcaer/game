#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <bgfx/bgfx.h>

#include "shader/shadermanager.hpp"

struct Renderer {
  static constexpr bgfx::ViewId
    VIEW_MAIN = 0;

  ShaderManager shader_manager;

  Renderer();
  ~Renderer();

  void init(unsigned width, unsigned height);

  void resize(unsigned width, unsigned height);

  void prepare_frame();

  void end_frame();
};

#endif