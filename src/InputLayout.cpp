#include "InputLayout.h"
#include "Error.h"

namespace dxr {

InputLayout::InputLayout(const Blobs* blobs)
	: p_blobs(blobs) {}

void InputLayout::bind() const {
	RUN(context()->IASetInputLayout(m_layout.Get()), device());
}

void InputLayout::addLayout(D3D11_INPUT_ELEMENT_DESC desc) {
	m_layouts.push_back(std::move(desc));
}

void InputLayout::createLayout() {
	HRUN(device()->CreateInputLayout(
		m_layouts.data(),
		m_layouts.size(),
		p_blobs->vsBlob->GetBufferPointer(),
		p_blobs->vsBlob->GetBufferSize(),
		m_layout.GetAddressOf()
	));
}

}