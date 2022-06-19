#include "shadermanager.hpp"

#include <assert.h>
#include <fstream>

#include "global.hpp"

ShaderManager::ShaderManager() = default;  

void ShaderManager::init() {
  auto shader_settings = global.settings["shaders"].as_table();
  assert(shader_settings != nullptr);

  for (auto&& [key, val] : *shader_settings) {
    std::string name = std::string(key.str());
    auto sources = val.as_table();
    std::string vs_path = sources->get("vertex")->as_string()->get();
    std::string fs_path = sources->get("fragment")->as_string()->get();

    load_shader(name, vs_path, fs_path);
  }
}

void ShaderManager::load_shader(const std::string name, const std::string vs_path, const std::string fs_path) {
  auto vsh = process_shader(vs_path);
  auto fsh = process_shader(fs_path);

  auto program = bgfx::createProgram(vsh, fsh, true);
  m_shaders.insert({ name, program });
}

bgfx::ProgramHandle ShaderManager::get_shader(const std::string name) {
  assert(m_shaders.contains(name));

  return m_shaders[name];
}

bgfx::ShaderHandle ShaderManager::process_shader(const std::string path) {
  std::ifstream fs(path);
  fs.seekg(0, std::ios::end);
  size_t size = fs.tellg();
  fs.seekg(0);
  
  const bgfx::Memory* mem = bgfx::alloc(size+ 1);
  fs.read((char*)mem->data, size);

  return bgfx::createShader(mem);
}
