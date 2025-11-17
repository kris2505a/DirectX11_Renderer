#include "Shader.h"
#include <d3dcompiler.h>
#include "ErrorH.h"

Shader::Shader(const std::wstring& path) {
    createShader(ShaderType::vertexShader, path);
    createShader(ShaderType::pixelShader, path);
}

void Shader::bind() const {
    RUN(context()->VSSetShader(m_vertexShader.Get(), nullptr, 0), device());
    RUN(context()->PSSetShader(m_pixelShader.Get(), nullptr, 0), device());
}

void Shader::unbind() const {
    ID3D11VertexShader* nullvsShader = nullptr;
    ID3D11PixelShader* nullpsShader = nullptr;
    RUN(context()->VSSetShader(nullptr, nullptr, 0), device());
    RUN(context()->PSSetShader(nullptr, nullptr, 0), device());
}

const Blobs* Shader::getBlobs() const {
    return &m_blobs;
}

void Shader::createShader(ShaderType type, const std::wstring& path) {
    std::wstring tmpPath = path;
    if (type == ShaderType::vertexShader) {
        tmpPath += L"VertexShader.cso";
        HRUN(D3DReadFileToBlob(tmpPath.c_str(), &m_blobs.vsBlob));
        HRUN(device()->CreateVertexShader(
            m_blobs.vsBlob->GetBufferPointer(), 
            m_blobs.vsBlob->GetBufferSize(), 
            nullptr, 
            &m_vertexShader
        ));
    }
    else if (type == ShaderType::pixelShader) {
        tmpPath += L"PixelShader.cso";
        HRUN(D3DReadFileToBlob(tmpPath.c_str(), &m_blobs.psBlob));
        HRUN(device()->CreatePixelShader(
            m_blobs.psBlob->GetBufferPointer(),
            m_blobs.psBlob->GetBufferSize(),
            nullptr, 
            &m_pixelShader
        ));
    }
}
