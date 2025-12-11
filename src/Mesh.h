#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

class Mesh {
	friend class CubeMeshed;
public:
	Mesh() = default;
	~Mesh();

	static Mesh* cubeMesh();

private:
	VertexBuffer* m_vbo;
	IndexBuffer* m_ibo;
};