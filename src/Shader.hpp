#pragma once
#include "BindsBase.hpp"
#include <string>
#include "Blobs.hpp"

class Shader : public BindsBase {
public:
    Shader(const std::wstring& vsPath, const std::wstring& psPath);
    ~Shader() = default;
    void bind() const final override;
    const Blobs* blobs() const;

private:
    void compileShader(wrl::ComPtr <ID3DBlob>& blobs, const std::wstring& file, const std::string& entrypoint, const std::string& target);

private:
    wrl::ComPtr <ID3D11VertexShader> m_vertexShader;
    wrl::ComPtr <ID3D11PixelShader> m_pixelShader;
    Blobs m_blobs;
};