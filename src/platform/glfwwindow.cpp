#include "platform/platform.hpp"

#include <assert.h>
// TODO: support other OSs
#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3native.h>

GLFWWindow::GLFWWindow(glm::vec2 size, const char* title) { 
  assert(glfwInit()); 

  m_window = glfwCreateWindow(size.x, size.y, title, nullptr, nullptr);
  m_size = size;
}

GLFWWindow::~GLFWWindow() {
  glfwDestroyWindow(m_window);
  glfwTerminate();
}

bool GLFWWindow::is_close_requested() {
  return glfwWindowShouldClose(m_window);
}

glm::vec2 GLFWWindow::size() {
  return m_size;
}

bool GLFWWindow::resized() {
  int width, height;
  glfwGetWindowSize(m_window, &width, &height);

  if (width != m_size.x || height != m_size.y) {
    m_size.x = width;
    m_size.y = height;

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
