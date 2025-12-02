#pragma once
#include "Binds.h"
#include <wrl/client.h>

class VertexBuffer : public Binds {
public:
	VertexBuffer(const void* data, int size, unsigned int stride, unsigned int offset = 0);
	~VertexBuffer() = default;
	void bind() const final override;
	void unbind() const final override;

private:
	Microsoft::WRL::ComPtr <ID3D11Buffer> m_buffer;
	UINT m_stride, m_offset;
};