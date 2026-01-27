#include "Material.h"

namespace dxr {

std::shared_ptr <MaterialSharedStates> MaterialSharedStates::s_sharedInstance;

const DirectX::XMFLOAT4& Material::getColor() const {
	return m_color;
}

void Material::setColor(float r, float g, float b, float a) {
	m_color = { r, g, b, a };
}

std::unique_ptr<Material> Material::createSolidMaterial() {
	auto material = std::make_unique <Material>();
	material->m_type = MaterialType::SolidColor;
	material->m_color = { 0.8f, 0.8f, 0.8f, 1.0f };
	if (MaterialSharedStates::s_sharedInstance) {
		material->m_sharedState = MaterialSharedStates::s_sharedInstance;
		return material;
	}

	MaterialSharedStates::s_sharedInstance = std::make_shared <MaterialSharedStates>();
	MaterialSharedStates::s_sharedInstance->m_shader = 
		std::make_unique <Shader>(L"shader/DefVS.cso", L"shader/DefPS.cso");
	MaterialSharedStates::s_sharedInstance->m_ilo = 
		std::make_unique <InputLayout>(MaterialSharedStates::s_sharedInstance->m_shader->blobs());

	MaterialSharedStates::s_sharedInstance->m_ilo->addLayout({
		"POSITION", 
		0, 
		DXGI_FORMAT_R32G32B32_FLOAT, 
		0, 
		0, 
		D3D11_INPUT_PER_VERTEX_DATA, 
		0
	});

	MaterialSharedStates::s_sharedInstance->m_ilo->addLayout({
		"NORMAL",
		0,
		DXGI_FORMAT_R32G32B32_FLOAT,
		0,
		D3D11_APPEND_ALIGNED_ELEMENT,
		D3D11_INPUT_PER_VERTEX_DATA,
		0
		});

	MaterialSharedStates::s_sharedInstance->m_ilo->addLayout({
		"TEXCOORD", 
		0, 
		DXGI_FORMAT_R32G32_FLOAT, 
		0, 
		D3D11_APPEND_ALIGNED_ELEMENT, 
		D3D11_INPUT_PER_VERTEX_DATA, 
		0
	});

	MaterialSharedStates::s_sharedInstance->m_ilo->createLayout();

	material->m_sharedState = MaterialSharedStates::s_sharedInstance;
	return material;
}

void Material::setTexture(const std::string& path) {
	m_type = MaterialType::Texture;
	m_texture = std::make_unique <Texture>(path);
}

void Material::bind() const {
	if (auto shared = m_sharedState.lock()) {
		shared->m_shader->bind();
		shared->m_ilo->bind();
	}
	if (m_type == MaterialType::Texture) {
		m_texture->bind();
	}
}

}