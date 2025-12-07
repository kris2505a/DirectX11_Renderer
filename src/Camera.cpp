#include "Camera.h"
#include "imgui.h"
#include "Mouse.h"
#include "Keyboard.h"
#include <algorithm>

Camera::Camera()
	: m_zoom(-15.0f), m_pitch(0.0f), m_yaw(0.0f), m_sensitivity(0.005f), m_speed(1.0f) {

	m_position = dx::XMVectorSet(0.0f, 0.0f, -3.0f, 1.0f);
	m_up = dx::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	m_forward = dx::XMVector3Normalize(
		dx::XMVectorSet(
			cosf(m_pitch) * sinf(m_yaw),
			sinf(m_pitch),
			cosf(m_pitch) * cosf(m_yaw),
			0.0f
		)
	);


	m_up = dx::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	m_view = dx::XMMatrixLookAtLH(m_position, dx::XMVectorZero(), m_up);
	m_projection = dx::XMMatrixPerspectiveFovLH(dx::XMConvertToRadians(45.0f), 16.0f / 9.0f, 0.5f, 20.0f);

	Mouse::lockMouse(true);

}

void Camera::update(float deltaTime) {

	if (Keyboard::isKeyDown(kQ)) {
		Mouse::m_locked = !Mouse::m_locked;
	}

	float dx = Mouse::m_deltaX;
	float dy = Mouse::m_deltaY;

	ImGui::Begin("Camera");
	ImGui::Text("Pitch, Yaw: %f, %f", m_pitch, m_yaw);
	ImGui::Text("Mouse: %f, %f", dx, dy);
	ImGui::End();
	
	m_yaw += dx * m_sensitivity;
	m_pitch -= dy * m_sensitivity;



	m_pitch = std::clamp(m_pitch, -dx::XM_PIDIV2 + 0.01f, dx::XM_PIDIV2 - 0.01f);

	m_forward = dx::XMVector3Normalize(
		dx::XMVectorSet(
			cosf(m_pitch) * sinf(m_yaw),
			sinf(m_pitch),
			cosf(m_pitch) * cosf(m_yaw),
			0.0f
		)
	);

	m_right = dx::XMVector3Normalize(dx::XMVector3Cross(m_up, m_forward));

	if (Keyboard::isKeyDown(kS)) {
		m_position = dx::XMVectorAdd(m_position, dx::XMVectorScale(m_forward, m_speed * deltaTime));
	}
	if (Keyboard::isKeyDown(kW)) {
		m_position = dx::XMVectorSubtract(m_position, dx::XMVectorScale(m_forward, m_speed * deltaTime));
	}
	if (Keyboard::isKeyDown(kD)) {
		m_position = dx::XMVectorSubtract(m_position, dx::XMVectorScale(m_right, m_speed * deltaTime));
	}
	if (Keyboard::isKeyDown(kA)) {
		m_position = dx::XMVectorAdd(m_position, dx::XMVectorScale(m_right, m_speed * deltaTime));
	}


	m_view = dx::XMMatrixLookAtLH(m_position, dx::XMVectorAdd(m_position, m_forward), m_up);
	Mouse::m_deltaX = 0.0f;
	Mouse::m_deltaY = 0.0f;
}

dx::XMMATRIX& Camera::view() {
	return m_view;
}

dx::XMMATRIX& Camera::projection() {
	return m_projection;
}
