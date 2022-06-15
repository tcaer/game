#ifndef MESH_HPP
#define MESH_HPP

#include <assert.h>
#include <cstdint>

struct Mesh {
  virtual void load(void* data) { assert(false); }

  virtual void bind() { assert(false); }

  virtual uint16_t instance_stride() { assert(false); }
  virtual uint32_t num_instances() { assert(false); }
};

#endif
