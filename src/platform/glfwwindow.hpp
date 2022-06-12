#ifndef GLFWWINDOW_HPP
#define GLFWWINDOW_HPP

#include <GLFW/glfw3.h>
#include <bgfx/platform.h>

struct GLFWWindow {
  GLFWwindow* m_window;
  unsigned m_width, m_height;

  GLFWWindow(unsigned width, unsigned height, const char* title);
  ~GLFWWindow();

  bool is_close_requested();

  unsigned width();
  unsigned height();

  bool resized();

  void set_platform_data(bgfx::PlatformData& platform_data);

  void prepare_frame();
};

#endif