#include "InputLayout.h"
#include "Shader.h"
#include "ErrorH.h"

InputLayout::InputLayout(const Blobs* blobs) : p_blobs(blobs) {}

void InputLayout::bind() const {
	RUN(context()->IASetInputLayout(m_layout.Get()), device());
}

void InputLayout::unbind() const {
	ID3D11InputLayout* nullLayout = nullptr;
	context()->IASetInputLayout(nullLayout);
}

void InputLayout::addLayout(D3D11_INPUT_ELEMENT_DESC desc) {
	m_desc.push_back(desc);
}

void InputLayout::createLayouts() {
	HRUN(device()->CreateInputLayout(
		m_desc.data(),
		std::size(m_desc),
		p_blobs->vsBlob->GetBufferPointer(),
		p_blobs->vsBlob->GetBufferSize(),
		&m_layout
	));
}
