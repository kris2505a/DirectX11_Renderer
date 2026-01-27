#pragma once
#include "BindsBase.h"
#include <string>

namespace dxr {

class Texture : public BindsBase {
public:
	Texture(const std::string& path);
	~Texture() = default;
	void bind() const final override;

private:
	wrl::ComPtr <ID3D11Texture2D> m_texture;
	wrl::ComPtr <ID3D11ShaderResourceView> m_textureResourceView;
	std::string m_path;
};

}