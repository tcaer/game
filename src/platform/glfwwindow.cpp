#include "platform/platform.hpp"

#include <assert.h>
// TODO: support other OSs
#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3native.h>

GLFWWindow::GLFWWindow(unsigned width, unsigned height, const char* title) {
  assert(glfwInit()); 

  m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
  m_width = width;
  m_height = height;
}

GLFWWindow::~GLFWWindow() {
  glfwDestroyWindow(m_window);
  glfwTerminate();
}

bool GLFWWindow::is_close_requested() {
  return glfwWindowShouldClose(m_window);
}

unsigned GLFWWindow::width() {
  return m_width;
}

unsigned GLFWWindow::height() {
  return m_height;
}

bool GLFWWindow::resized() {
  int width, height;
  glfwGetWindowSize(m_window, &width, &height);

  if (width != m_width || height != m_height) {
    m_width = width;
    m_height = height;

    return true;
  }

  return false;
}

void GLFWWindow::set_platform_data(bgfx::PlatformData& platform_data) {
  platform_data.nwh = glfwGetCocoaWindow(m_window);
}

void GLFWWindow::prepare_frame() {
  glfwPollEvents();
}