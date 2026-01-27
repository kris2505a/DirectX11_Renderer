#include "Renderer.h"
#include "Error.h"

struct VertexConstantBufferData {
	DirectX::XMMATRIX invModel;
	DirectX::XMMATRIX mvp;
};

struct PixelConstantBufferData {
	DirectX::XMFLOAT4 color;
	int hasTexture = 0;
	//int padding[3];
};

Renderer* Renderer::s_instance = nullptr;

Renderer::Renderer(HWND handle) {
	p_handle = handle;
	m_renderWidth = 1600;
	m_renderHeight = 900;
	m_clearColor = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_viewPort = {};

	if(!s_instance) {
		s_instance = this;
	}

	createDeviceSwapChain();
	createRenderTargetView();
	//createDepthStencilState();
	//createDepthStencilView();
	createViewPort();
	createRasterizerState();
	createSamplerState();

	preRenderImpl();

	//temp bindings
	VertexConstantBufferData vcd;
	vcd.invModel = DirectX::XMMatrixIdentity();
	vcd.mvp = DirectX::XMMatrixIdentity();
	m_vertexCBO = std::make_unique <ConstantBuffer>(&vcd, sizeof(vcd), ShaderType::VertexShader);
	
	PixelConstantBufferData pcd;
	pcd.color = { 0.0f, 0.0f, 0.0f, 1.0f };
	pcd.hasTexture = 0;
	m_pixelCBO = std::make_unique <ConstantBuffer>(&pcd, sizeof(pcd), ShaderType::PixelShader);

	p_activeCamera = nullptr;
}

#pragma region Initializations

void Renderer::createDeviceSwapChain() {
	DXGI_SWAP_CHAIN_DESC sd                 = {};
	sd.BufferDesc.Width                     = 0;
	sd.BufferDesc.Height                    = 0;
	sd.BufferDesc.RefreshRate.Numerator     = 0;
	sd.BufferDesc.RefreshRate.Denominator   = 0;
	sd.BufferDesc.Format                    = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering          = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
	sd.BufferDesc.Scaling                   = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.SampleDesc.Count                     = 1;
	sd.SampleDesc.Quality                   = 0;
	sd.BufferCount                          = 1;
	sd.OutputWindow                         = p_handle;
	sd.BufferUsage                          = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.Windowed                             = true;
	sd.SwapEffect                           = DXGI_SWAP_EFFECT_DISCARD;

	unsigned int debugFlags                 = 0;

#ifdef _DEBUG
	debugFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // _DEBUG

	HRUN(D3D11CreateDeviceAndSwapChain(
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
	));
}

void Renderer::createRenderTargetView() {
	wrl::ComPtr<ID3D11Texture2D> pBackBuffer;
	HRUN(m_swapchain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer)));

	D3D11_TEXTURE2D_DESC bbDesc;
	pBackBuffer->GetDesc(&bbDesc);

	m_renderWidth = bbDesc.Width;
	m_renderHeight = bbDesc.Height;
	HRUN(m_device->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &m_targetView));
	
}


void Renderer::createViewPort() {
	m_viewPort.TopLeftX       = 0;
	m_viewPort.TopLeftY       = 0;
	m_viewPort.Width          = static_cast <float>(m_renderWidth);
	m_viewPort.Height         = static_cast <float>(m_renderHeight);
	m_viewPort.MinDepth		  = 0.0f;
	m_viewPort.MaxDepth		  = 1.0f;
}

void Renderer::createDepthStencilState() {

	D3D11_DEPTH_STENCIL_DESC dsd = {};
	dsd.DepthEnable				 = TRUE;
	dsd.DepthWriteMask			 = D3D11_DEPTH_WRITE_MASK_ALL;
	dsd.DepthFunc				 = D3D11_COMPARISON_LESS;
	dsd.StencilEnable			 = FALSE;

	HRUN(m_device->CreateDepthStencilState(&dsd, &m_stencilState));

}

void Renderer::createDepthStencilView() {


	D3D11_TEXTURE2D_DESC td = {};
	td.Width                = m_renderWidth;
	td.Height               = m_renderHeight;
	td.MipLevels            = 1;
	td.ArraySize			= 1;
	td.Format				= DXGI_FORMAT_D24_UNORM_S8_UINT;
	td.SampleDesc.Quality   = 0;
	td.SampleDesc.Count		= 1;
	td.Usage				= D3D11_USAGE_DEFAULT;
	td.BindFlags			= D3D11_BIND_DEPTH_STENCIL;
	td.CPUAccessFlags		= 0;
	td.MiscFlags			= 0;

	wrl::ComPtr <ID3D11Texture2D> depthTexture;
	HRUN(m_device->CreateTexture2D(&td, nullptr, &depthTexture));

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd = {};
	dsvd.Format						   = td.Format;
	dsvd.ViewDimension				   = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvd.Texture2D.MipSlice			   = 0;

	HRUN(m_device->CreateDepthStencilView(depthTexture.Get(), &dsvd, &m_stencilView));
	
}

void Renderer::createRasterizerState() {
	D3D11_RASTERIZER_DESC rd{};

	rd.DepthClipEnable = true;
	rd.FrontCounterClockwise = true;
	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_BACK;

	HRUN(m_device->CreateRasterizerState(&rd, m_rasterizerState.GetAddressOf()));
	RUN(m_context->RSSetState(m_rasterizerState.Get()), m_device);
}

void Renderer::createSamplerState() {
	D3D11_SAMPLER_DESC sd{};
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	HRUN(m_device->CreateSamplerState(&sd, m_samplerState.GetAddressOf()));
	RUN(m_context->PSSetSamplers(0, 1, m_samplerState.GetAddressOf()), m_device);
}

#pragma endregion

void Renderer::preRenderImpl() {
	ID3D11RenderTargetView* rtvs[] = { m_targetView.Get() };

	RUN(m_context->OMSetRenderTargets(1, rtvs, m_stencilView.Get()), m_device);
	RUN(m_context->OMSetDepthStencilState(m_stencilState.Get(), 0), m_device);
	RUN(m_context->RSSetViewports(1, &m_viewPort), m_device);
	RUN(m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST), m_device);

	this->clear();
}

void Renderer::clear() {
	RUN(m_context->ClearRenderTargetView(m_targetView.Get(), m_clearColor.data()), m_device);
	RUN(m_context->ClearDepthStencilView(m_stencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0), m_device);
}

void Renderer::swap() {
	RUN(m_swapchain->Present(1, 0), m_device);
}

void Renderer::drawIndexed(unsigned int count) {
	RUN(m_context->DrawIndexed(count, 0, 0), m_device);
}

void Renderer::renderImpl(const Entity* entity) {
	entity->m_mesh->bind();
	entity->m_material->bind();

	auto model = entity->getTransform().model();

	VertexConstantBufferData vcbd;
	
	vcbd.invModel = DirectX::XMMatrixTranspose(
		DirectX::XMMatrixInverse(
			nullptr, model
		)
	);


	if (p_activeCamera) {
		vcbd.mvp = DirectX::XMMatrixTranspose(
			entity->getTransform().model() *
			p_activeCamera->viewMat() *
			p_activeCamera->projMat()
		);
	}

	else {
		vcbd.mvp = DirectX::XMMatrixTranspose(
			entity->getTransform().model() *
			m_defaultCamera.viewMat() *
			m_defaultCamera.projMat()
		);
	}
	
	m_vertexCBO->update(&vcbd, sizeof(vcbd));

	PixelConstantBufferData pcbd;
	
	pcbd.color = entity->m_material->getColor();
	
	if (entity->m_material->m_type == MaterialType::Texture) {
		pcbd.hasTexture = 1;
	}

	m_pixelCBO->update(&pcbd, sizeof(pcbd));

	m_vertexCBO->bind();
	m_pixelCBO->bind();
	RUN(m_context->DrawIndexed(entity->m_mesh->getIndexCount(), 0, 0), m_device);
}

void Renderer::postRenderImpl() {
	this->swap();
}

void Renderer::setActiveCamera(Camera* camera) {
	p_activeCamera = camera;
}

void Renderer::preRender() {
	if (!s_instance)
		return;
	s_instance->preRenderImpl();
}

void Renderer::postRender() {
	if (!s_instance)
		return;
	s_instance->postRender();
}

void Renderer::renderSubmit(const Entity* entity) {
	if (!s_instance)
		return;
	s_instance->renderImpl(entity);
}

ID3D11Device* Renderer::getDevice() {
	if (!s_instance)
		return nullptr;
	return s_instance->m_device.Get();
}

ID3D11DeviceContext* Renderer::getContext() {
	if (!s_instance)
		return nullptr;
	return s_instance->m_context.Get();
}


Renderer::~Renderer() {

}