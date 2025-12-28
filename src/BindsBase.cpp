#include "BindsBase.hpp"
#include "Renderer.hpp"

ID3D11Device* BindsBase::device() const {
    return Renderer::s_instance->m_device.Get();
}

ID3D11DeviceContext* BindsBase::context() const {
    return Renderer::s_instance->m_context.Get();
}