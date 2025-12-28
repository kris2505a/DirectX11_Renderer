#pragma once
#include "BindsBase.hpp"

class IndexBuffer : public BindsBase {
public:
    IndexBuffer(const void* indices, unsigned int count, unsigned int offset = 0);
    ~IndexBuffer() = default;
    void bind() const final override;
    unsigned int indexCount() const;

private:
    wrl::ComPtr <ID3D11Buffer> m_buffer;
    unsigned int m_offset;
    unsigned int m_count;
};