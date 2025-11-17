#include "Binds.h"
#include "Renderer.h"
#include <print>

ID3D11Device* Binds::device() const {
    if (!Renderer::s_instance) {
        std::println("renderer is null");
        return nullptr;
    }
    return Renderer::s_instance->m_device.Get();
}

ID3D11DeviceContext* Binds::context() const {
    if (!Renderer::s_instance) {
        std::println("renderer is null");
        return nullptr;
    }
    return Renderer::s_instance->m_context.Get();
}

IDXGISwapChain* Binds::swapChain() const {
    if (!Renderer::s_instance) {
        std::println("renderer is null");
        return nullptr;
    }
    return Renderer::s_instance->m_swapchain.Get();
}
