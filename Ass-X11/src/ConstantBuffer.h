#pragma once
#include "Binds.h"
#include "Shader.h"

class ConstantBuffer : public Binds {
public:
	ConstantBuffer(const void* data, int size, ShaderType type);
	~ConstantBuffer() = default;

	void bind() const final override;
	void unbind() const final override;
	void update(const void* data, int size);

private:
	ShaderType m_type;
	Microsoft::WRL::ComPtr <ID3D11Buffer> m_buffer;
};