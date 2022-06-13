#ifndef GLFWWINDOW_HPP
#define GLFWWINDOW_HPP

#include <GLFW/glfw3.h>
#include <bgfx/platform.h>
#include <glm/glm.hpp>

struct GLFWWindow {
  GLFWwindow* m_window;
  glm::vec2 m_size;

  GLFWWindow(glm::vec2 size, const char* title);
  ~GLFWWindow();

  bool is_close_requested();

  glm::vec2 size();

  bool resized();

  void set_platform_data(bgfx::PlatformData& platform_data);

  void prepare_frame();
};

#endif
