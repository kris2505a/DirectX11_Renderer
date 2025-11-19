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

Cube::Cube() {

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

	addBuffer(std::make_unique<VertexBuffer>(vertices, sizeof(vertices), sizeof(Vertex)));
	
	addIndexBuffer(std::make_unique<IndexBuffer>(indices, sizeof(indices), std::size(indices)));

	auto shader = std::make_unique<Shader>(L"shader/");
	auto blobs = shader->getBlobs();
	addBuffer(std::move(shader));

	auto ilo = std::make_unique <InputLayout>(blobs);
	ilo->addLayout({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 });
	ilo->addLayout({ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 });
	ilo->createLayouts();
	addBuffer(std::move(ilo));


	rotation = { 0.0f, 0.0f, 0.0f };
	position = { 0.0f, 0.0f, 0.0f };
	scale = { 1.0f, 1.0f, 1.0f };

	auto model = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z) *
		DirectX::XMMatrixTranslation(position.x, position.y, position.z) *
		DirectX::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);

	auto view = DirectX::XMMatrixLookAtLH(
		{ 0.0f, 0.0f, -3.0f, 1.0f },
		{ 0.0f, 0.0f, 0.0f, 0.0f},
		{ 0.0f, 1.0f, 0.0f, 1.0f}
	);

	auto projection = DirectX::XMMatrixPerspectiveFovLH(45.0f, 16.0f / 9.0f, 0.5f, 10.0f);

	mat = XMMatrixTranspose(model * view * projection);

	auto cbo = std::make_unique<ConstantBuffer>(&mat, sizeof(mat), ShaderType::vertexShader);
	p_cbo = cbo.get();

	addBuffer(std::move(cbo));

}

void Cube::update(float deltaTime) {

	float speed = 2.0f;

	if (Keyboard::isKeyDown(KEY_A)) {
		rotation.y += speed * deltaTime;
	}
	if (Keyboard::isKeyDown(KEY_D)) {
		rotation.y -= speed * deltaTime;
	}
	if (Keyboard::isKeyDown(KEY_S)) {
		rotation.x -= speed * deltaTime;
	}
	if (Keyboard::isKeyDown(KEY_W)) {
		rotation.x += speed * deltaTime;
	}
	


	auto model = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z) *
		DirectX::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z) *
		DirectX::XMMatrixTranslation(position.x, position.y, position.z);

	auto view = DirectX::XMMatrixLookAtLH(
		{ 0.0f, 0.0f, -3.0f, 1.0f },
		{ 0.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f, 1.0f }
	);

	auto projection = DirectX::XMMatrixPerspectiveFovLH(degToRad(45.0f), 16.0f / 9.0f, 0.5f, 10.0f);

	mat = XMMatrixTranspose(model * view * projection);
	p_cbo->update(&mat, sizeof(mat));
	
}
