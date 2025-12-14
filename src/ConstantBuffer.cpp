#include "ConstantBuffer.h"
#include "ErrorH.h"

ConstantBuffer::ConstantBuffer(const void* data, int size, ShaderType type, int slot)
	: m_type(type), m_slot(slot) {
	
	D3D11_BUFFER_DESC cbd;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0;
	cbd.ByteWidth = (size + 15) & ~15;
	cbd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA crd;
	crd.pSysMem = data;

	HRUN(device()->CreateBuffer(&cbd, &crd, &m_buffer));

}

void ConstantBuffer::bind() const {
	if (m_type == ShaderType::vertexShader) {
		RUN(context()->VSSetConstantBuffers(m_slot, 1, m_buffer.GetAddressOf()), device());
	}
	else if (m_type == ShaderType::pixelShader) {
		RUN(context()->PSSetConstantBuffers(m_slot, 1, m_buffer.GetAddressOf()), device());
	}
}

void ConstantBuffer::unbind() const {
	ID3D11Buffer* nullbuffer = nullptr;
	if (m_type == ShaderType::vertexShader) {
		RUN(context()->VSSetConstantBuffers(0, 1, &nullbuffer), device());
	}
	else if (m_type == ShaderType::pixelShader) {
		RUN(context()->PSSetConstantBuffers(0, 1, &nullbuffer), device());
	}
}

void ConstantBuffer::update(const void* data, int size) {
	D3D11_MAPPED_SUBRESOURCE mappedRes;
	RUN(context()->Map(m_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedRes), device());
	memcpy(mappedRes.pData, data, size);
	RUN(context()->Unmap(m_buffer.Get(), 0), device());

}
