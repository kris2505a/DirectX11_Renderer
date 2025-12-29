#pragma once
#include <WRL/client.h>
#include <d3d11.h>
#include <array>

#include "ConstantBuffer.hpp"
#include "Transform.hpp"
#include "Shader.hpp"
#include "InputLayout.hpp"

namespace wrl = Microsoft::WRL;

class Renderer {
    friend class BindsBase;
    friend class Entity;

public:
    Renderer(HWND handle);
    ~Renderer();
    void clear();
    void preRender();
    void swap();
    void drawIndexed(unsigned int count);
    void renderBinded(Transform* transform, unsigned int indexCount, dx::XMFLOAT4 color) {
        auto mvp = dx::XMMatrixTranspose(transform->model() * m_view * m_proj);
        m_vcbo->update(&mvp, sizeof(mvp));
        m_vcbo->bind();
        m_pcbo->update(&color, sizeof(color));
        m_pcbo->bind();
        m_ilo->bind();
        m_shader->bind();

        drawIndexed(indexCount);
    }

private:
	void createDeviceSwapChain();
	void createRenderTargetView();
	void createViewPort();
	void createDepthStencilState();
	void createDepthStencilView();

private:
    wrl::ComPtr <ID3D11Device> m_device;
    wrl::ComPtr <ID3D11DeviceContext> m_context;
    wrl::ComPtr <IDXGISwapChain> m_swapchain;
    wrl::ComPtr <ID3D11RenderTargetView> m_targetView;
	wrl::ComPtr <ID3D11DepthStencilView> m_stencilView;
	wrl::ComPtr <ID3D11DepthStencilState> m_stencilState;
	std::array <float, 4> m_clearColor;

	D3D11_VIEWPORT m_viewPort;

    int m_renderWidth;
    int m_renderHeight;

    HWND p_handle;
    dx::XMMATRIX m_view;
    dx::XMMATRIX m_proj;

//rendering
    ConstantBuffer* m_vcbo;
    ConstantBuffer* m_pcbo;
    Shader* m_shader;
    InputLayout* m_ilo;

    static Renderer* s_instance;

};