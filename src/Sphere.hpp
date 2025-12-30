#pragma once
#include "Entity.hpp"
#include "Mesh.hpp"

class Sphere : public Entity {
public:
	Sphere() {
		m_mesh = Mesh::sphereMesh().get();
		indexCount(m_mesh->indexCount());
	}
	~Sphere() = default;
	void update(float deltaTime) {

	}

	void bind() final override {
		m_mesh->bind();
	}

private:
	Mesh* m_mesh;
};