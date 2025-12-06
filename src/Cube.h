#pragma once
#include "ConstantBuffer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "InputLayout.h"
#include <DirectXMath.h>
#include "Camera.h"

struct Vector {
	float x, y, z;
};

class Cube {
public:
	Cube(Camera* curCamera, float x, float y, float z);
	~Cube();
	unsigned int getIndexCount() const;
	void bind();
	void unbind();
	void update(float deltaTime);

private:
	ConstantBuffer* cbo = nullptr;
	VertexBuffer* vbo = nullptr;
	IndexBuffer* ibo = nullptr;
	InputLayout* ilo = nullptr;
	Shader* shader = nullptr;

	DirectX::XMMATRIX mat;
	Vector position, rotation, scale;
	Camera* p_camera;

};