#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include "platform/platform.hpp"
#include "renderer/renderer.hpp"

struct Global {
  Platform* platform;
  Renderer* renderer;
};

extern Global global;

#endif
