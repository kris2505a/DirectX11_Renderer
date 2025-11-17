#pragma once
#include "Binds.h"
#include <wrl/client.h>

class IndexBuffer : public Binds {
public:
	IndexBuffer(const void* data, int size, unsigned int offset = 0);
	~IndexBuffer() = default;
	void bind() const final override;
	void unbind() const final override;

private:
	Microsoft::WRL::ComPtr <ID3D11Buffer> m_buffer;
	UINT m_offset;
};