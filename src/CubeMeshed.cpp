#include "CubeMeshed.h"
#include <imgui.h>

int CubeMeshed::s_cubeId = 0;

CubeMeshed::CubeMeshed(Mesh* mesh, Material* mat, Camera* cam)
	: p_mesh(mesh), p_material(mat), p_camera(cam), m_transform(nullptr) {

	m_transform = new Transform;
	auto matr = dx::XMMatrixTranspose(m_transform->m_model * p_camera->view() * p_camera->projection());

	m_vcbo = new ConstantBuffer(&matr, sizeof(matr), ShaderType::vertexShader);
	
	m_color = { 0.0f, 1.0f, 1.0f, 1.0f };
	m_pcbo = new ConstantBuffer(&m_color, sizeof(m_color), ShaderType::pixelShader);

	s_cubeId++;
	m_name = "Cube: " + std::to_string(s_cubeId);
}

CubeMeshed::~CubeMeshed() {
	delete m_transform;
	delete m_vcbo;
	delete m_pcbo;
}

void CubeMeshed::update(float deltaTime) {
	m_transform->update();
	auto matr = dx::XMMatrixTranspose(m_transform->m_model * p_camera->view() * p_camera->projection());
	m_vcbo->update(&matr, sizeof(matr));
}

void CubeMeshed::render(ID3D11DeviceContext* context) {

	ImGui::Begin(m_name.c_str());
	
	ImGui::InputFloat("X", &m_transform->m_position.x);
	ImGui::InputFloat("Y", &m_transform->m_position.y);
	ImGui::InputFloat("Z", &m_transform->m_position.z);

	ImGui::End();

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
