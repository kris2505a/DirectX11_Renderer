#include "Shader.hpp"
#include <iostream>
#include "Error.hpp"

Shader::Shader(const std::wstring& vsPath, const std::wstring& psPath) {
    compileShader(m_blobs.vsBlob, vsPath, "main", "vs_5_0");
    compileShader(m_blobs.psBlob, psPath, "main", "ps_5_0");

    HRUN(device()->CreateVertexShader(
		m_blobs.vsBlob->GetBufferPointer(),
		m_blobs.vsBlob->GetBufferSize(),
		nullptr,
		m_vertexShader.GetAddressOf()
	));
	HRUN(device()->CreatePixelShader(
		m_blobs.psBlob->GetBufferPointer(),
		m_blobs.psBlob->GetBufferSize(),
		nullptr,
		m_pixelShader.GetAddressOf()
	));


}

void Shader::compileShader(
    wrl::ComPtr <ID3DBlob>& blob, const std::wstring& file, const std::string& entrypoint, const std::string& target) {

    unsigned int flags = D3DCOMPILE_ENABLE_STRICTNESS;

#ifdef _DEBUG
    flags |= D3DCOMPILE_DEBUG;
    flags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
    wrl::ComPtr<ID3DBlob> errorBlob;
    HRESULT hr = D3DCompileFromFile(
        file.c_str(),
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        entrypoint.c_str(),
        target.c_str(),
        flags,
        0,
        blob.GetAddressOf(),
        errorBlob.GetAddressOf()
    );

    if(FAILED(hr)) {
        if(errorBlob) {
            std::cout << "HLSL compile error:\n\n";
            std::cout << "File: " << std::string(file.begin(), file.end()) << "\n";
            std::cout << "Entry: " << entrypoint << "\n";
            std::cout << "Target: " << target << "\n\n";

            std::cout << (char*)errorBlob->GetBufferPointer() << "\n";
        }
        else {
            std::cout << "Unknown HLSL compile error!" << std::endl;
        }
        std::exit(1);
    }
}


void Shader::bind() const {
	RUN(context()->VSSetShader(m_vertexShader.Get(), nullptr, 0), device());
	RUN(context()->PSSetShader(m_pixelShader.Get(), nullptr, 0), device());
}

const Blobs* Shader::blobs() const {
    return &m_blobs;
}