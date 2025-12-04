#pragma once
#include "Draws.h"
#include "ConstantBuffer.h"
#include <DirectXMath.h>
#include "Camera.h"

struct Vector {
	float x, y, z;
};

class Cube : Draws {
public:
	Cube();
	~Cube() = default;
	unsigned int getIndexCount() const;
	void bindall();
	void unbindall();
	void update(float deltaTime);

private:
	ConstantBuffer* p_cbo = nullptr;
	DirectX::XMMATRIX mat;
	Vector position, rotation, scale;
	Camera m_camera;

};