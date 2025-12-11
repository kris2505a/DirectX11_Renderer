#include "Material.h"


Material::~Material() {
	if (m_shader) 
		delete m_shader;
	if (m_ilo) 
		delete m_ilo;
}

Material* Material::createMaterial() {
	Material* mat = new Material;
	mat->m_shader = new Shader(L"shader/");
	mat->m_ilo = new InputLayout(mat->m_shader->getBlobs());

	mat->m_ilo->addLayout({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 });
	mat->m_ilo->addLayout({ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 });
	mat->m_ilo->createLayouts();

	return mat;
}
