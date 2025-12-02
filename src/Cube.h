#pragma once
#include "Draws.h"
#include "ConstantBuffer.h"
#include <DirectXMath.h>

struct Vector {
	float x, y, z;
};

class Cube : Draws {
public:
	Cube();
	~Cube() = default;
	unsigned int getIndexCount() const {
		return p_indexBuffer->getIndexCount();
	}
	void bindall() {
		this->bind();
	}
	void unbindall() {
		this->unbind();
	}
	void update(float deltaTime);

private:
	ConstantBuffer* p_cbo = nullptr;
	DirectX::XMMATRIX mat;
	Vector position, rotation, scale;
	
};