#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <DirectXMath.h>

namespace wrl = Microsoft::WRL;

class Renderer {
	friend class Binds;
	friend class App;

public:
	Renderer(HWND handle);
	~Renderer();
	void wipeOff();
	void flipBuffers();
	void clearColor(float r, float g, float b, float a);
	void vSync(bool condition);
	void indexedRender(int size);

private:
	void createDeviceAndSwapChain(HWND handle);
	void createRenderTargetView();
	void createViewport();
	void createDepthStencil();
	void setViewPortAndDepthStencil();
	void createSamplerState();

private:
	wrl::ComPtr <ID3D11Device> m_device;
	wrl::ComPtr <ID3D11DeviceContext> m_context;
	wrl::ComPtr <IDXGISwapChain> m_swapchain;
	wrl::ComPtr <ID3D11RenderTargetView> m_targetView;
	wrl::ComPtr <ID3D11DepthStencilView> m_stencilView;
	wrl::ComPtr <ID3D11SamplerState> m_samplerState;

	float m_clearColor[4];

	DirectX::XMMATRIX m_view, m_projection;

private:
	static Renderer* s_instance;
	bool m_vSync;
};