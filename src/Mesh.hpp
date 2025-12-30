#pragma once
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include <memory>

class Mesh {
public:
	void bind() const;
	static std::shared_ptr <Mesh> cubeMesh();
	static std::shared_ptr <Mesh> sphereMesh();
	unsigned int indexCount() const;

private:
	Mesh() {}

private:
	std::unique_ptr <VertexBuffer> m_vbo;
	std::unique_ptr <IndexBuffer> m_ibo;
	
	static std::shared_ptr <Mesh> s_cubeMesh;
	static std::shared_ptr <Mesh> s_sphereMesh;

};