#pragma once
#include <DirectXMath.h>

namespace dx = DirectX;

class Transform {
	friend class CubeMeshed;

public:
	Transform();
	~Transform() = default;
	void update();

private:
	dx::XMMATRIX m_model;
	dx::XMFLOAT3 m_position;
	dx::XMFLOAT3 m_rotation;
	dx::XMFLOAT3 m_scale;
};