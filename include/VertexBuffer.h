#pragma once
#include "BindsBase.h"

namespace dxr {

class VertexBuffer : public BindsBase {
public:
    VertexBuffer(const void* vertices, unsigned int count, unsigned int stride, unsigned int offset = 0);
    ~VertexBuffer() = default;
    void bind() const final override;

private:
    wrl::ComPtr <ID3D11Buffer> m_buffer;
    unsigned int m_stride;
    unsigned int m_offset;
};

}