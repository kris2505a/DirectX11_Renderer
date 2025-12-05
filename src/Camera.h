#pragma once
#include <DirectXMath.h>

namespace dx = DirectX;

class Camera {
public:
	Camera();
	~Camera() = default;

	void update(float deltaTime);
	dx::XMMATRIX& getView();

private:
	dx::XMMATRIX m_view;
	dx::XMVECTOR m_forward, m_right, m_up, m_world, m_position;
	float m_pitch, m_yaw;
	float m_speed;
	float m_zoom;
};