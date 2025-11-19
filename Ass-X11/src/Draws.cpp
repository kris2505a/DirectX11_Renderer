#include "Draws.h"


void Draws::addBuffer(std::unique_ptr<Binds> buffer) {
	m_binds.push_back(std::move(buffer));
}

void Draws::addIndexBuffer(std::unique_ptr<IndexBuffer> buffer) {
	p_indexBuffer = buffer.get();
	m_binds.push_back(std::move(buffer));
}

void Draws::bind() {
	for (auto& i : m_binds) {
		i->bind();
	}

}

void Draws::unbind() {
	for (auto& i : m_binds) {
		i->unbind();
	}
}