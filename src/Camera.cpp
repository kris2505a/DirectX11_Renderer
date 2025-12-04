#include "Camera.h"

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
    
}

void Camera::update(float deltaTime) {
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
