#include "VertexBuffer.h"
#include "ErrorH.h"

VertexBuffer::VertexBuffer(const void* data, int size, unsigned int stride, unsigned int offset) 
	: m_stride(stride), m_offset(offset) {
	D3D11_BUFFER_DESC vbd = {};
	vbd.Usage = D3D11_USAGE_DYNAMIC;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vbd.MiscFlags = 0;
	vbd.ByteWidth = size;
	vbd.StructureByteStride = stride;

	D3D11_SUBRESOURCE_DATA vsd = {};
	vsd.pSysMem = data;

	HRUN(device()->CreateBuffer(&vbd, &vsd, &m_buffer));
}

void VertexBuffer::bind() const {
	RUN(context()->IASetVertexBuffers(0, 1, m_buffer.GetAddressOf(), &m_stride, &m_offset), device());
}

void VertexBuffer::unbind() const {
	ID3D11Buffer* nullBuffer = nullptr;
	UINT stride = 0;
	UINT offset = 0;
	context()->IASetVertexBuffers(0, 1, &nullBuffer, &stride, &offset);
}
