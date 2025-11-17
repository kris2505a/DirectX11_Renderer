#pragma once
#include "Binds.h"
#include "wrl/client.h"
#include <vector>
#include <string>

struct Blobs;

class InputLayout : public Binds {
public:
	InputLayout(const Blobs* blobs);
	~InputLayout() = default;

	void bind() const final override;
	void unbind() const final override;

	void addLayout(D3D11_INPUT_ELEMENT_DESC desc);
	void createLayouts();

private:
	Microsoft::WRL::ComPtr <ID3D11InputLayout> m_layout;
	std::vector <D3D11_INPUT_ELEMENT_DESC> m_desc;
	const Blobs* p_blobs;
};