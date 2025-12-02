#include "Texture.h"
#include "stb_image.h"
#include <print>
#include "ErrorH.h"

Texture::Texture(const std::string& path) {
	int width, height, bpp;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &bpp, STBI_rgb_alpha);
	if (!data) {
		std::println("unable to load texture via stb_image");
	}

	D3D11_TEXTURE2D_DESC td = {};
	td.Width = width;
	td.Height = height;
	td.MipLevels = 1;
	td.ArraySize = 1;
	td.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	td.SampleDesc.Count = 1;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	D3D11_SUBRESOURCE_DATA srd = {};
	srd.pSysMem = data;
	srd.SysMemPitch = width * 4;

	HRUN(device()->CreateTexture2D(&td, &srd, &m_texture));

	HRUN(device()->CreateShaderResourceView(m_texture.Get(), nullptr, &m_srView));

	if(data)
		stbi_image_free(data);
}

void Texture::bind() const {
	RUN(context()->PSSetShaderResources(0, 1, m_srView.GetAddressOf()), device());
}

void Texture::unbind() const {
	ID3D11ShaderResourceView* nullsrv = nullptr;
	context()->PSSetShaderResources(0, 1, &nullsrv);
}