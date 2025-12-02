#pragma once
#include <memory>
#include <vector>
#include "Binds.h"
#include "IndexBuffer.h"


class Draws {

	friend class Renderer;

public:
	Draws() = default;
	virtual ~Draws() = default;
	void bind();
	void unbind();

protected:
	void addBuffer(std::unique_ptr <Binds> buffer);
	void addIndexBuffer(std::unique_ptr <IndexBuffer> buffer);


	IndexBuffer* p_indexBuffer = nullptr;

private:
	std::vector <std::unique_ptr <Binds>> m_binds;
};