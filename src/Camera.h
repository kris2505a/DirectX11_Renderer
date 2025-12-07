#pragma once
#include <DirectXMath.h>

namespace dx = DirectX;

class Camera {
public:
	Camera();
	~Camera() = default;
	void update(float deltaTime);
	dx::XMMATRIX& view();
	dx::XMMATRIX& projection();


private:
	dx::XMMATRIX m_view;
	dx::XMMATRIX m_projection;

	dx::XMVECTOR m_position;

	dx::XMVECTOR m_forward;
	dx::XMVECTOR m_right;
	dx::XMVECTOR m_up;
	
	float m_zoom;
	float m_pitch;
	float m_yaw;
	float m_sensitivity;
	float m_speed;
};