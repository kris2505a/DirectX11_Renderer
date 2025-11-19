#pragma once
#include <string>
#include "Binds.h"
#include <wrl/client.h>

class Texture : public Binds {
public:
	Texture(const std::string& path);
	~Texture() = default;

	void bind() const final override;
	void unbind() const final override;

private:
	Microsoft::WRL::ComPtr <ID3D11Texture2D> m_texture;
	Microsoft::WRL::ComPtr <ID3D11ShaderResourceView> m_srView;
};