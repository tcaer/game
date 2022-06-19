#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <bgfx/bgfx.h>
#include <glm/glm.hpp>

#include "gfx/shader/shadermanager.hpp"
#include "gfx/texture/texturemanager.hpp"

struct Renderer {
  static constexpr bgfx::ViewId
    VIEW_MAIN = 0;

  ShaderManager shader_manager;
  TextureManager texture_manager;

  Renderer();
  ~Renderer();

  void init(glm::vec2 window_size);

  void resize(glm::vec2 window_size);

  void prepare_frame();

  void end_frame();
};

#endif
