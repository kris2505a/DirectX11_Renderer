#include "Window.h"
#include "Renderer.h"
#include "ErrorH.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "InputLayout.h"
#include "ConstantBuffer.h"
#include <DirectXMath.h>


#define device renderer->m_device
#define context renderer->m_context

int main() {
	Window* window = new Window(GetModuleHandle(nullptr));
	Renderer* renderer = new Renderer(window->getHandle());
	renderer->vSync(true);

	renderer->clearColor(0.0f, 0.0f, 0.0f, 1.0f);

	float vertices[]{
		-0.5f,  0.5f,  0.5f, //0
		 0.5f, -0.5f,  0.5f, //1
		-0.5f, -0.5f,  0.5f, //2
		 0.5f,  0.5f,  0.5f, //3

		 /*
		-0.5f,  0.5f, -0.5f, //4
		 0.5f, -0.5f, -0.5f, //5
		-0.5f, -0.5f, -0.5f, //6
		 0.5f,  0.5f, -0.5f  //7
		 */
	};

	unsigned int indices[]{
		// Front face (z = +0.5)
		0, 2, 1,
		0, 1, 3,

		/* Back face (z = -0.5)
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
		*/
	};


	VertexBuffer vbo(vertices, sizeof(vertices), 3 * sizeof(float));
	IndexBuffer ibo(indices, sizeof(indices));
	Shader shader(L"shader/");
	InputLayout ilo(shader.getBlobs());

	ilo.addLayout({ "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 });
	ilo.createLayouts();

	struct CBuf {
		DirectX::XMMATRIX mat;
	};

	CBuf cb;

	auto view = DirectX::XMMatrixLookAtLH(
		DirectX::XMVectorSet(0.0f, 0.0f, -3.0f, 0.0f), // camera pos
		DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),  // look at origin
		DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)   // up direction
	);

	auto proj = DirectX::XMMatrixPerspectiveFovLH(
		1.0f,
		1.0f,
		0.1f,
		100.0f
	);
	cb.mat = DirectX::XMMatrixTranspose(
		DirectX::XMMatrixScaling((9.0f / 16.0f), 1.0f, 1.0f) *
		view * proj
	);
	ConstantBuffer cbo(&cb, sizeof(cb), ShaderType::vertexShader);

	struct CBuf2 {
		DirectX::XMFLOAT4 color[6];
	};

	CBuf2 cb2{
		{
			{1.0f, 0.0f, 0.0f, 1.0f},
			{0.0f, 1.0f, 0.0f, 1.0f},
			{0.0f, 0.0f, 1.0f, 1.0f},
			{1.0f, 1.0f, 0.0f, 1.0f},
			{0.0f, 1.0f, 1.0f, 1.0f},
			{1.0f, 0.0f, 1.0f, 1.0f}
		}
	};

	//ConstantBuffer cbo2(&cb2, sizeof(cb2), ShaderType::pixelShader);

	float angle = 10.0f;






	while (window->isOpen()) {
		window->handleMessages();
		renderer->wipeOff();

		//constant buffer matrix


		//Bind calls
		vbo.bind();
		ibo.bind();
		shader.bind();
		ilo.bind();
		cbo.bind();
		//cbo2.bind();

		//Draw Call
		renderer->indexedRender(std::size(indices));

		//Unbind calls
		//cbo2.unbind();
		cbo.unbind();
		ilo.unbind();
		shader.unbind();
		ibo.unbind();
		vbo.unbind();

		renderer->flipBuffers();

		angle += 1.0f;
		if (angle >= 360.0f) angle = 0.0f;

	}

	delete renderer;
	delete window;
}