#include "Camera.h"
#include "Keyboard.h"
#include <imgui.h>

Camera::Camera() {
    m_pitch = 0;
    m_yaw = 0;

    float x = cos(m_pitch) * cos(m_yaw);
    float y = sin(m_pitch);
    float z = cos(m_pitch) * sin(m_yaw);

    m_forward = dx::XMVectorSet(x, y, z, 0.0f);
    m_world = dx::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    m_position = dx::XMVectorSet(0.0f, 0.0f, -3.0f, 0.0f);

    m_right = dx::XMVector3Normalize(dx::XMVector3Cross(m_world, m_forward));
    m_up = dx::XMVector3Normalize(dx::XMVector3Cross(m_forward, m_right));
    m_speed = 20.0f;
    m_zoom = -1.0f;
}

void Camera::update(float deltaTime) {

    //if (Keyboard::isKeyDown(VK_UP)) {
    //    m_pitch += m_speed * deltaTime;
    //}
    //if (Keyboard::isKeyDown(VK_DOWN)) {
    //    m_pitch -= m_speed * deltaTime;
    //}
    //if (Keyboard::isKeyDown(VK_LEFT)) {
    //    m_yaw += m_speed * deltaTime;
    //}
    //if (Keyboard::isKeyDown(VK_RIGHT)) {
    //    m_yaw -= m_speed * deltaTime;
    //}

    ImGui::Begin("Camera");

    ImGui::DragFloat("Camera Zoom", &m_zoom, 0.1f, -50.0f, 50.0f);

    ImGui::End();
    ImGui::Render();

    m_position = dx::XMVectorSetY(m_position, m_zoom);

    float x = cos(m_pitch) * cos(m_yaw);
    float y = sin(m_pitch);
    float z = cos(m_pitch) * sin(m_yaw);

    m_forward = dx::XMVectorSet(x, y, z, 0.0f);
    m_forward = dx::XMVector3Normalize(m_forward);
    m_right = dx::XMVector3Normalize(dx::XMVector3Cross(m_world, m_forward));
    m_up = dx::XMVector3Normalize(dx::XMVector3Cross(m_forward, m_right));

    m_view = dx::XMMatrixLookAtLH(m_position, m_forward, m_world);

}

dx::XMMATRIX& Camera::getView() {
    return m_view;
}
