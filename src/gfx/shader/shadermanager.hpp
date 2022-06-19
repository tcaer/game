#ifndef SHADERMANAGER_HPP
#define SHADERMANAGER_HPP

#include <unordered_map>
#include <string>
#include <bgfx/bgfx.h>

struct ShaderManager {
  ShaderManager();

  void init();

  bgfx::ProgramHandle get_shader(const std::string name);

private:
  std::unordered_map<std::string, bgfx::ProgramHandle> m_shaders;

  void load_shader(const std::string name, const std::string vs_path, const std::string fs_path);
  bgfx::ShaderHandle process_shader(const std::string path);
};

#endif
