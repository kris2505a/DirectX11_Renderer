#pragma once
#include "BindsBase.hpp"
#include "Blobs.hpp"
#include <vector>


class InputLayout : public BindsBase {
public:
	InputLayout(const Blobs* blobs);
	~InputLayout() = default;
	void bind() const final override;
	void addLayout(D3D11_INPUT_ELEMENT_DESC desc);
	void createLayout();

private:
	wrl::ComPtr <ID3D11InputLayout> m_layout;
	std::vector <D3D11_INPUT_ELEMENT_DESC> m_layouts;

	const Blobs* p_blobs;
};
