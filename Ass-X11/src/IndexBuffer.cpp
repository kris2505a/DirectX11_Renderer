#include "IndexBuffer.h"
#include "ErrorH.h"

IndexBuffer::IndexBuffer(const void* data, int size, unsigned int offset) : m_offset(offset){
	D3D11_BUFFER_DESC ibd = {};
	ibd.Usage = D3D11_USAGE_DYNAMIC;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	ibd.MiscFlags = 0;
	ibd.ByteWidth = size;
	ibd.StructureByteStride = sizeof(unsigned int);

	D3D11_SUBRESOURCE_DATA isd = {};
	isd.pSysMem = data;

	HRUN(device()->CreateBuffer(&ibd, &isd, &m_buffer));
}

void IndexBuffer::bind() const {
	RUN(context()->IASetIndexBuffer(m_buffer.Get(), DXGI_FORMAT_R32_UINT, 0), device());
}

void IndexBuffer::unbind() const {
	ID3D11Buffer* nullBuffer = nullptr;
	UINT stride = 0;
	UINT offset = 0;
	context()->IASetIndexBuffer(nullBuffer, DXGI_FORMAT_UNKNOWN, offset);
}
