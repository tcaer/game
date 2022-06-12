#ifndef SHADERMANAGER_HPP
#define SHADERMANAGER_HPP

#include <unordered_map>
#include <string>
#include <bgfx/bgfx.h>

struct ShaderManager {
  std::unordered_map<std::string, bgfx::ProgramHandle> m_shaders;

  ShaderManager();

  void load_shader(std::string name, std::string vs_path, std::string fs_path);

  bgfx::ProgramHandle get_shader(std::string name);

private:
  bgfx::ShaderHandle process_shader(std::string path);
};

#endif