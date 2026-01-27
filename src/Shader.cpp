#include "Shader.h"
#include <iostream>
#include "Error.h"
#include <d3dcompiler.h>

namespace dxr {

Shader::Shader(const std::wstring& vsPath, const std::wstring& psPath) {

    HRUN(D3DReadFileToBlob(vsPath.c_str(), &m_blobs.vsBlob));
    HRUN(D3DReadFileToBlob(psPath.c_str(), &m_blobs.psBlob));

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

void Shader::bind() const {
	RUN(context()->VSSetShader(m_vertexShader.Get(), nullptr, 0), device());
	RUN(context()->PSSetShader(m_pixelShader.Get(), nullptr, 0), device());
}

const Blobs* Shader::blobs() const {
    return &m_blobs;
}

}