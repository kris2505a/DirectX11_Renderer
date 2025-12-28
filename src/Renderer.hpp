#pragma once
#include <WRL/client.h>
#include <d3d11.h>
#include <array>

namespace wrl = Microsoft::WRL;

class Renderer {
    friend class BindsBase;

public:
    Renderer(HWND handle);
    ~Renderer() = default;
    void clear();
    void preRender();
    void swap();
    void drawIndexed(unsigned int count);

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

    static Renderer* s_instance;

};