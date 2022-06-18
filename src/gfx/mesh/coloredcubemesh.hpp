#ifndef COLOREDCUBEMESH_HPP
#define COLOREDCUBEMESH_HPP

#include <bgfx/bgfx.h>

#include "gfx/mesh/mesh.hpp"

struct ColoredCubeMesh : Mesh {
  ~ColoredCubeMesh();

  void load(void* data);

  void bind();

  uint16_t instance_stride();
  uint32_t num_instances();

public:
  struct PosColorVertex {
    float x;
    float y;
    float z;
    uint32_t color;
    float tx;
    float ty;
  };
  static PosColorVertex m_vertices[];
  
  static const uint16_t m_cubeTriList[];

  bgfx::VertexBufferHandle m_vbh;
  bgfx::IndexBufferHandle m_ibh;

  const uint16_t STRIDE = 4*4*sizeof(float) + 4*sizeof(float);
  const uint32_t NUM_INSTANCES = 1000;
};

#endif
