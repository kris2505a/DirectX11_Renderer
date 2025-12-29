#include "ConstantBuffer.hpp"
#include "Error.hpp"

ConstantBuffer::ConstantBuffer(const void* data, int size, ShaderType type)
	: m_type(type) {
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; 
	bd.MiscFlags = 0;
	bd.ByteWidth = (size + 15) & ~15;
	bd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA srd = {};
	srd.pSysMem = data;

	HRUN(device()->CreateBuffer(&bd, &srd, &m_buffer));
}

void ConstantBuffer::bind() const {
	if (m_type == ShaderType::VertexShader) {
		RUN(context()->VSSetConstantBuffers(0, 1, m_buffer.GetAddressOf()), device());
	}
	else if (m_type == ShaderType::PixelShader) {
		RUN(context()->PSSetConstantBuffers(0, 1, m_buffer.GetAddressOf()), device());
	}
}

void ConstantBuffer::update(const void* data, int size) {
	D3D11_MAPPED_SUBRESOURCE map;
	RUN(context()->Map(m_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &map), device());
	memcpy(map.pData, data, size);
	RUN(context()->Unmap(m_buffer.Get(), 0), device());
}