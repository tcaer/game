#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <toml++/toml.h>

#include "platform/platform.hpp"
#include "renderer/renderer.hpp"

struct Global {
  Platform* platform;
  Renderer* renderer;

  toml::table settings;
};

extern Global global;

#endif
