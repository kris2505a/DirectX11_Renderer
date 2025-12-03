#pragma once
#include <DirectXMath.h>

namespace dx = DirectX;

class Camera {
public:

private:
	dx::XMMATRIX m_view;
	dx::XMFLOAT3 m_centre;
};