#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <unordered_map>
#include <string>
#include <bgfx/bgfx.h>

struct TextureManager {
  TextureManager();

  void init();

  bgfx::TextureHandle get_texture(const std::string name); 

private:
  std::unordered_map<std::string, bgfx::TextureHandle> m_textures;

  void load_texture(const std::string name, const std::string path);
};

#endif
