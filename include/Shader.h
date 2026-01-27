#pragma once
#include "BindsBase.h"
#include <string>
#include "Blobs.h"

namespace dxr {

class Shader : public BindsBase {
public:
    Shader(const std::wstring& vsPath, const std::wstring& psPath);
    ~Shader() = default;
    void bind() const final override;
    const Blobs* blobs() const;

private:
    wrl::ComPtr <ID3D11VertexShader> m_vertexShader;
    wrl::ComPtr <ID3D11PixelShader> m_pixelShader;
    Blobs m_blobs;
};

}