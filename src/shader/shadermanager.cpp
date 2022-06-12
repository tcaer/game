#include "shadermanager.hpp"

#include <assert.h>
#include <fstream>

ShaderManager::ShaderManager() = default;

void ShaderManager::load_shader(std::string name, std::string vs_path, std::string fs_path) {
  auto vsh = process_shader(vs_path);
  auto fsh = process_shader(fs_path);

  auto program = bgfx::createProgram(vsh, fsh, true);
  m_shaders.insert({ name, program });
}

bgfx::ProgramHandle ShaderManager::get_shader(std::string name) {
  assert(m_shaders.contains(name));

  return m_shaders[name];
}

bgfx::ShaderHandle ShaderManager::process_shader(std::string path) {
  std::ifstream fs(path);
  fs.seekg(0, std::ios::end);
  size_t size = fs.tellg();
  fs.seekg(0);
  
  const bgfx::Memory* mem = bgfx::alloc(size+ 1);
  fs.read((char*)mem->data, size);

  return bgfx::createShader(mem);
}