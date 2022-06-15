#include "gfx/mesh/coloredcubemesh.hpp"

ColoredCubeMesh::PosColorVertex ColoredCubeMesh::m_vertices[] = {
  {-1.0f,  1.0f,  1.0f, 0xff000000 },
	{ 1.0f,  1.0f,  1.0f, 0xff0000ff },
	{-1.0f, -1.0f,  1.0f, 0xff00ff00 },
	{ 1.0f, -1.0f,  1.0f, 0xff0000ff },
	{-1.0f,  1.0f, -1.0f, 0xffff00ff },
	{ 1.0f,  1.0f, -1.0f, 0xffffffff },
	{-1.0f, -1.0f, -1.0f, 0xff00ffff },
	{ 1.0f, -1.0f, -1.0f, 0xffffff00 }
};

const uint16_t ColoredCubeMesh::m_cubeTriList[] = {
	0, 1, 2,
	1, 3, 2,
	4, 6, 5,
	5, 6, 7,
	0, 2, 4,
	4, 2, 6,
	1, 5, 3,
	5, 7, 3,
	0, 4, 1,
	4, 5, 1,
	2, 3, 6,
	6, 3, 7,
};

ColoredCubeMesh::~ColoredCubeMesh() {
	bgfx::destroy(m_vbh);
	bgfx::destroy(m_ibh);
}

void ColoredCubeMesh::load(void* data) {
	bgfx::VertexLayout layout;
	layout.begin()
		.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
	.end();
	m_vbh = bgfx::createVertexBuffer(bgfx::makeRef(m_vertices, sizeof(m_vertices)), layout);
	m_ibh = bgfx::createIndexBuffer(bgfx::makeRef(m_cubeTriList, sizeof(m_cubeTriList)));
}

void ColoredCubeMesh::bind() {
	bgfx::setVertexBuffer(0, m_vbh);
	bgfx::setIndexBuffer(m_ibh);
}

uint16_t ColoredCubeMesh::instance_stride() {
	return STRIDE;
}

uint32_t ColoredCubeMesh::num_instances() {
	return NUM_INSTANCES;
}
