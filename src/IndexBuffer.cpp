#include "IndexBuffer.hpp"
#include <cstdint>
#include "Error.hpp"

IndexBuffer::IndexBuffer(const void* indices, unsigned int count, unsigned int offset) 
    : m_offset(offset), m_count(count) {
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.ByteWidth = count * sizeof(uint32_t);
	bd.StructureByteStride = sizeof(uint32_t);

	D3D11_SUBRESOURCE_DATA srd = {};
	srd.pSysMem = indices;

	HRUN(device()->CreateBuffer(&bd, &srd, &m_buffer));
}

void IndexBuffer::bind() const {
	RUN(context()->IASetIndexBuffer(m_buffer.Get(), DXGI_FORMAT_R32_UINT, m_offset), device());
}

unsigned int IndexBuffer::indexCount() const {
	return m_count;
}
