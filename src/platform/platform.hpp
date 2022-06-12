#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include <memory>

#include "platform/glfwwindow.hpp"

struct Platform {
  std::unique_ptr<GLFWWindow> window;
};

#endif