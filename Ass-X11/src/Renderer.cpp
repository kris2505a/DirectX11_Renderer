#include "Renderer.h"
#include "ErrorH.h"
#include <print>

Renderer* Renderer::s_instance = nullptr;

Renderer::Renderer(HWND handle) : m_vSync(true) {

	if (s_instance) {
		std::println("Instance of Renderer already exists!");
		std::abort();
	}
	s_instance = this;
	this->createDeviceAndSwapChain(handle);
	this->createRenderTargetView();
	this->createDepthStencil();
	this->setViewPortAndDepthStencil();
	this->createViewport();

	//default clear color
	m_clearColor[0] = 0.0f;
	m_clearColor[1] = 0.0f;
	m_clearColor[2] = 0.0f;
	m_clearColor[3] = 1.0f;

	m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Renderer::createDeviceAndSwapChain(HWND handle) {
	DXGI_SWAP_CHAIN_DESC sd = { 0 };
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferCount = 2;
	sd.OutputWindow = handle;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.Windowed = true;

	unsigned int debugFlags = 0;

#ifdef _DEBUG
	debugFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // _DEBUG

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		debugFlags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&m_swapchain,
		&m_device,
		nullptr,
		&m_context
	);
	if (FAILED(hr)) {
		MessageBoxA(nullptr, "Failed to create D3D11 device/swapchain", "Error", MB_OK);
	}
}

void Renderer::createRenderTargetView() {
	ID3D11Resource* p_backBuffer = nullptr;
	m_swapchain->GetBuffer(0, __uuidof(ID3D11Resource), (void**)&p_backBuffer);

	if (!p_backBuffer) {
		std::println("unable to fetch back buffer");
		std::abort();
	}
	HRESULT hr = m_device->CreateRenderTargetView(p_backBuffer, nullptr, &m_targetView);

	if (FAILED(hr)) {
		MessageBoxA(nullptr, "Failed to create D3D11 device/swapchain", "Error", MB_OK);
	}
	p_backBuffer->Release();
}

void Renderer::createViewport() {
	D3D11_VIEWPORT vp = { 0 };
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	vp.Width = 1600.0f;
	vp.Height = 900.0f;
	
	m_context->RSSetViewports(1, &vp);
}

void Renderer::createDepthStencil() {

	DXGI_SWAP_CHAIN_DESC swapDesc = {};
	m_swapchain->GetDesc(&swapDesc);

	D3D11_TEXTURE2D_DESC t2d = { 0 };
	t2d.Width = swapDesc.BufferDesc.Width;
	t2d.Height = swapDesc.BufferDesc.Height;
	t2d.MipLevels = 1;
	t2d.ArraySize = 1;
	t2d.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	t2d.SampleDesc.Count = 1;
	t2d.SampleDesc.Quality = 0;
	t2d.Usage = D3D11_USAGE_DEFAULT;
	t2d.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	t2d.CPUAccessFlags = 0;
	t2d.MiscFlags = 0;

	wrl::ComPtr <ID3D11Texture2D> depthStencilTexture;
	HRUN(m_device->CreateTexture2D(&t2d, nullptr, &depthStencilTexture));

	D3D11_DEPTH_STENCIL_VIEW_DESC dsv = {};
	dsv.Format = t2d.Format;
	dsv.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsv.Texture2D.MipSlice = 0;

	HRUN(m_device->CreateDepthStencilView(depthStencilTexture.Get(), &dsv, &m_stencilView));

}

void Renderer::setViewPortAndDepthStencil() {
	RUN(m_context->OMSetRenderTargets(1, m_targetView.GetAddressOf(), m_stencilView.Get()), m_device);
}

void Renderer::wipeOff() {
	RUN(m_context->ClearRenderTargetView(m_targetView.Get(), m_clearColor), m_device);
	RUN(m_context->ClearDepthStencilView(m_stencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0), m_device);
}

void Renderer::flipBuffers() {
	m_swapchain->Present(m_vSync, 0);
}

void Renderer::clearColor(float r, float g, float b, float a) {
	m_clearColor[0] = r;
	m_clearColor[1] = g;
	m_clearColor[2] = b;
	m_clearColor[3] = a;
}

void Renderer::vSync(bool condition) {
	m_vSync = condition;
}

void Renderer::indexedRender(int size) {
	RUN(m_context->DrawIndexed(size, 0, 0), m_device);
}
