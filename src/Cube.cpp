#include "Cube.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "InputLayout.h"
#include "ConstantBuffer.h"
#include "Vertex.h"
#include "Mouse.h"
#include "Keyboard.h"


#define KEY_W 0x57
#define KEY_A 0x41
#define KEY_S 0x53
#define KEY_D 0x44



auto degToRad = [](float deg) { return deg * DirectX::XM_PI / 180.0f; };

Cube::Cube(Camera* camera, float x, float y, float z) : p_camera(camera) {

	Vertex vertices[]{
		{{-0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 1.0f, 1.0f}},
		{{ 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 0.0f, 1.0f}},
		{{-0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 1.0f, 1.0f}},
		{{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 1.0f, 1.0f}},
		{{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 0.0f, 1.0f}},
		{{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 1.0f, 1.0f}},
		{{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 1.0f, 1.0f}},
		{{ 0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 1.0f, 1.0f}}
	};

	unsigned int indices[]{
		// Front face (z = +0.5)
		0, 2, 1,
		0, 1, 3,

		// Back face (z = -0.5)
		4, 5, 6,
		4, 7, 5,

		// Left face (x = -0.5)
		4, 6, 2,
		4, 2, 0,

		// Right face (x = +0.5)
		3, 1, 5,
		3, 5, 7,

		// Top face (y = +0.5)
		4, 0, 3,
		4, 3, 7,

		// Bottom face (y = -0.5)
		1, 2, 6,
		1, 6, 5
	};

	this->vbo = new VertexBuffer(vertices, sizeof(vertices), sizeof(Vertex));
	this->ibo = new IndexBuffer(indices, sizeof(indices), std::size(indices));
	this->shader = new Shader(L"shader/");
	this->ilo = new InputLayout(shader->getBlobs());

	ilo->addLayout({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 });
	ilo->addLayout({ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 });
	ilo->createLayouts();


	rotation = { 0.0f, 0.0f, 0.0f };
	position = { x, y, z };
	scale = { 1.0f, 1.0f, 1.0f };

	auto model = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z) *
		DirectX::XMMatrixTranslation(position.x, position.y, position.z) *
		DirectX::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);

	dx::XMVECTOR eye = dx::XMVectorSet(0.0f, 0.0f, -3.0f, 0.0f);
	dx::XMVECTOR target = dx::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	dx::XMVECTOR up = dx::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	auto view = dx::XMMatrixLookAtLH(eye, target, up);

	auto projection = DirectX::XMMatrixPerspectiveFovLH(45.0f, 16.0f / 9.0f, 0.5f, 10.0f);

	mat = XMMatrixTranspose(model * view * projection);

	cbo = new ConstantBuffer(&mat, sizeof(mat), ShaderType::vertexShader);

}

void Cube::update(float deltaTime) {

	/*
	float speed = 2.0f;

	if (Keyboard::isKeyDown(KEY_A)) {
		rotation.y -= speed * deltaTime;
	}
	if (Keyboard::isKeyDown(KEY_D)) {
		rotation.y += speed * deltaTime;
	}
	if (Keyboard::isKeyDown(KEY_S)) {
		rotation.x += speed * deltaTime;
	}
	if (Keyboard::isKeyDown(KEY_W)) {
		rotation.x -= speed * deltaTime;
	}
	*/

	auto model = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z) *
		DirectX::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z) *
		DirectX::XMMatrixTranslation(position.x, position.y, position.z);

	

	mat = XMMatrixTranspose(model * p_camera->view() * p_camera->projection());
	cbo->update(&mat, sizeof(mat));
	
}

unsigned int Cube::getIndexCount() const {
	return ibo->getIndexCount();
}

void Cube::bind() {
	vbo->bind();
	ibo->bind();
	shader->bind();
	ilo->bind();
	cbo->bind();
}


void Cube::unbind() {
	vbo->unbind();
	ibo->unbind();
	shader->unbind();
	ilo->unbind();
	cbo->unbind();
}

Cube::~Cube() {
	delete vbo;
	delete ibo;
	delete ilo;
	delete cbo;
	delete shader;
}