#pragma once
#include "BindsBase.hpp"
#include "ShaderType.hpp"

class ConstantBuffer : public BindsBase {
public:
    ConstantBuffer(const void* data, int size, ShaderType type);
    ~ConstantBuffer() = default;
    void bind() const final override;
    void update(const void* data, int size);

private:
    wrl::ComPtr <ID3D11Buffer> m_buffer;
    ShaderType m_type;
};