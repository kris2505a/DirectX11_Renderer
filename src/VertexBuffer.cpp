#include "VertexBuffer.hpp"
#include "Error.hpp"

VertexBuffer::VertexBuffer(const void* data, unsigned int count, unsigned int stride, unsigned int offset)
	: m_stride(stride), m_offset(offset)
{

	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.ByteWidth = m_stride * count;
	bd.StructureByteStride = m_stride;

	D3D11_SUBRESOURCE_DATA srd = {};
	srd.pSysMem = data;

	HRUN(device()->CreateBuffer(&bd, &srd, &m_buffer));
}

void VertexBuffer::bind() const
{
	RUN(context()->IASetVertexBuffers(0, 1, m_buffer.GetAddressOf(), &m_stride, &m_offset), device());
}
