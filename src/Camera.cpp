#include "Camera.h"
#include "imgui.h"
#include "Mouse.h"

Camera::Camera()
	: m_zoom(-5.0f), m_pitch(0.0f), m_yaw(0.0f), m_sensitivity(1.0f) {

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


	float dx = (Mouse::m_xPos / 1600.0f) * 2.0f - 1.0f;
	float dy = 1.0f - (Mouse::m_yPos / 900.0f) * 2.0f;

	ImGui::Begin("Camera");
	ImGui::SliderFloat("Sensitivity", &m_sensitivity, 0.1f, 3.0f);
	ImGui::SliderFloat("Distance", &m_zoom, -1.0f, -20.0f);
	ImGui::Text("Mouse: %f, %f", dx, dy);
	ImGui::End();
	
	m_yaw = dx * m_sensitivity;
	m_pitch = dy * m_sensitivity;

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
