#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include "platform/platform.hpp"

struct Global {
  Platform* platform;
};

extern Global global;

#endif
