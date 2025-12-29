#pragma once
#include "Transform.hpp"
#include "ConstantBuffer.hpp"
#include "Renderer.hpp"
#include <memory>
#include <vector>

class Entity {
public:
	Transform* transform() {
		return &m_transform;
	}
	virtual void update(float deltaTime) = 0;

	void render() {
		bind();
		Renderer::s_instance->renderBinded(&m_transform, m_indexCount, color);
	}
	virtual void bind() = 0;
	Entity() = default;
	virtual ~Entity() = default;
	void indexCount(unsigned int count) {
		m_indexCount = count;
	}

	dx::XMFLOAT4 color{ 1.0f, 0.0f, 0.0f, 1.0f };

private:
	Transform m_transform;
	unsigned int m_indexCount;
};