#include "Camera.h"
#include "imgui.h"

Camera::Camera()
	: m_zoom(-5.0f), m_pitch(0.0f), m_yaw(0.0f) {

	float x = m_zoom * cosf(m_pitch) * sinf(m_yaw);
	float y = m_zoom * sinf(m_pitch);
	float z = m_zoom * cosf(m_pitch) * cosf(m_yaw);


	m_eye = dx::XMVectorSet(x, y, z, 0.0f);
	m_target = dx::XMVectorZero();
	m_up = dx::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	m_view = dx::XMMatrixLookAtLH(m_eye, m_target, m_up);
	m_projection = dx::XMMatrixPerspectiveFovLH(dx::XMConvertToRadians(45.0f), 16.0f / 9.0f, 0.5f, 20.0f);
}

void Camera::update(float deltaTime) {


	ImGui::Begin("Camera");
	ImGui::SliderFloat("Distance", &m_zoom, -1.0f, -20.0f);
	ImGui::SliderFloat("Pitch", &m_pitch, -dx::XM_PIDIV2 + 0.01f, dx::XM_PIDIV2 - 0.01f);
	ImGui::SliderFloat("Yaw", &m_yaw, -dx::XM_PI, dx::XM_PI);
	ImGui::End();
	

	float x = m_zoom * cosf(m_pitch) * sinf(m_yaw);
	float y = m_zoom * sinf(m_pitch);
	float z = m_zoom * cosf(m_pitch) * cosf(m_yaw);
	m_eye = dx::XMVectorSet(x, y, z, 0.0f);
	m_view = dx::XMMatrixLookAtLH(m_eye, m_target, m_up);
}

dx::XMMATRIX& Camera::view() {
	return m_view;
}

dx::XMMATRIX& Camera::projection() {
	return m_projection;
}
