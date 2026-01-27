#pragma once
#include <WRL/client.h>
#include <d3d11.h>
#include <array>
#include "Entity/Entity.h"
#include "ConstantBuffer.h"
#include "Components/Camera.h"

namespace wrl = Microsoft::WRL;

namespace dxr {

class Renderer {
    friend class BindsBase;
    friend class Entity;

public:
    Renderer(HWND handle);
    ~Renderer();
    void setActiveCamera(Camera* camera);
    
    static void preRender();
    static void postRender();
    static void renderSubmit(const Entity* entity);
    static ID3D11Device* getDevice();
    static ID3D11DeviceContext* getContext();
    

private:
    void drawIndexed(unsigned int count);
    void preRenderImpl();
    void renderImpl(const Entity* entity);
    void postRenderImpl();


	void createDeviceSwapChain();
	void createRenderTargetView();
	void createViewPort();
	void createDepthStencilState();
	void createDepthStencilView();
    void createRasterizerState();
    void createSamplerState();
    void clear();
    void swap();

private:
    wrl::ComPtr <ID3D11Device> m_device;
    wrl::ComPtr <ID3D11DeviceContext> m_context;
    wrl::ComPtr <IDXGISwapChain> m_swapchain;
    wrl::ComPtr <ID3D11RenderTargetView> m_targetView;
	wrl::ComPtr <ID3D11DepthStencilView> m_stencilView;
	wrl::ComPtr <ID3D11DepthStencilState> m_stencilState;
    wrl::ComPtr <ID3D11RasterizerState> m_rasterizerState;
    wrl::ComPtr <ID3D11SamplerState> m_samplerState;
	std::array <float, 4> m_clearColor;

	D3D11_VIEWPORT m_viewPort;

    int m_renderWidth;
    int m_renderHeight;

    HWND p_handle;

    std::unique_ptr <ConstantBuffer> m_vertexCBO;
    std::unique_ptr <ConstantBuffer> m_pixelCBO;

    Camera* p_activeCamera;
    Camera m_defaultCamera;

    static Renderer* s_instance;
};

}