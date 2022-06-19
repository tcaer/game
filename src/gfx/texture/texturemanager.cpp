#include "gfx/texture/texturemanager.hpp"

#include <assert.h>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "global.hpp"

TextureManager::TextureManager() = default;

void TextureManager::init() {
  auto texture_settings = global.settings["textures"].as_table();
  assert(texture_settings != nullptr);

  stbi_set_flip_vertically_on_load(true);

  for (auto&& [key, val] : *texture_settings) {
    std::string name = std::string(key.str());
    std::string path = val.as_string()->get();

    load_texture(name, path);
  }
}

void TextureManager::load_texture(const std::string name, const std::string path) {
  int width, height, num_channels;
  unsigned char* data = stbi_load(path.c_str(), &width, &height, &num_channels, 0);
  const bgfx::Memory* image_mem = bgfx::copy(data, width * height * num_channels);

  auto texture = bgfx::createTexture2D(width, height, false, 1, bgfx::TextureFormat::RGB8, BGFX_TEXTURE_NONE | BGFX_SAMPLER_NONE, image_mem);
  stbi_image_free(data);

  m_textures.insert({ name, texture }); 
}

bgfx::TextureHandle TextureManager::get_texture(const std::string name) {
  assert(m_textures.contains(name));

  return m_textures[name];
}
