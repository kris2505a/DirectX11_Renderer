#pragma once
#include "Binds.h"
#include <wrl/client.h>
#include <string>

enum ShaderType {
	vertexShader,
	pixelShader
};

struct Blobs {
	Microsoft::WRL::ComPtr <ID3DBlob> vsBlob;
	Microsoft::WRL::ComPtr <ID3DBlob> psBlob;
};

class Shader : public Binds {
public:
	Shader(const std::wstring& path);
	~Shader() = default;
	void bind() const final override;
	void unbind() const final override;
	
	const Blobs* getBlobs() const;

private:
	void createShader(ShaderType type, const std::wstring& path);

private:
	Microsoft::WRL::ComPtr <ID3D11VertexShader> m_vertexShader;
	Microsoft::WRL::ComPtr <ID3D11PixelShader> m_pixelShader;
	Blobs m_blobs;
};