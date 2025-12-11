#include "CubeMeshed.h"

CubeMeshed::CubeMeshed(Mesh* mesh, Material* mat, Camera* cam)
	: p_mesh(mesh), p_material(mat), p_camera(cam), m_transform(nullptr) {

	m_transform = new Transform;
	auto matr = dx::XMMatrixTranspose(m_transform->m_model * p_camera->view() * p_camera->projection());

	m_vcbo = new ConstantBuffer(&matr, sizeof(matr), ShaderType::vertexShader);
	
	m_color = { 0.0f, 1.0f, 1.0f, 1.0f };
	m_pcbo = new ConstantBuffer(&m_color, sizeof(m_color), ShaderType::pixelShader);

}

CubeMeshed::~CubeMeshed() {
	delete m_transform;
	delete m_vcbo;
	delete m_pcbo;
}

void CubeMeshed::update(float deltaTime) {
	m_transform->update();
	auto matr = dx::XMMatrixTranspose(m_transform->m_model * p_camera->view() * p_camera->projection());
	m_vcbo->update(&matr, sizeof(m_transform->m_model));
}

void CubeMeshed::render(ID3D11DeviceContext* context) {
	p_mesh->m_vbo->bind();
	p_mesh->m_ibo->bind();
	p_material->m_ilo->bind();
	p_material->m_shader->bind();
	m_vcbo->bind();
	m_pcbo->bind();

	context->DrawIndexed(p_mesh->m_ibo->getIndexCount(), 0, 0);

	p_mesh->m_vbo->unbind();
	p_mesh->m_ibo->unbind();
	p_material->m_ilo->unbind();
	p_material->m_shader->unbind();
	m_vcbo->unbind();
	m_pcbo->unbind();

}
