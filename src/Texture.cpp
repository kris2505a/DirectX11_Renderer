#include "Texture.h"
#include <stb_image.h>
#include <stdexcept>
#include "Error.h"

namespace dxr {

Texture::Texture(const std::string& path) 
	: m_path(path) {


	int width, height, bpp;
	unsigned char* data = stbi_load(&m_path[0], &width, &height, &bpp, STBI_rgb_alpha);
	if (!data) {
		stbi_failure_reason();
	}

	D3D11_TEXTURE2D_DESC td{};
	td.Width = width;
	td.Height = height;
	td.MipLevels = 1;
	td.ArraySize = 1;
	td.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	td.SampleDesc.Count = 1;
	td.Usage = D3D11_USAGE_IMMUTABLE;
	td.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	D3D11_SUBRESOURCE_DATA srd{};
	srd.pSysMem = data;
	srd.SysMemPitch = width * 4;

	HRUN(device()->CreateTexture2D(&td, &srd, m_texture.GetAddressOf()));
	HRUN(device()->CreateShaderResourceView(
		m_texture.Get(), 
		nullptr, 
		m_textureResourceView.GetAddressOf()
	));
	if (data) {
		stbi_image_free(data);
	}
}

void Texture::bind() const {
	RUN(context()->PSSetShaderResources(0, 1, m_textureResourceView.GetAddressOf()), device());
}

}