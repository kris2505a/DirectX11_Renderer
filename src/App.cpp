#include "App.h"
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

#include "CubeMeshed.h"

struct DLight {
	dx::XMFLOAT3 direction;
	float intensity;
	dx::XMFLOAT3 color;
	float padding;
};

App::App(HINSTANCE instance) : m_deltaTime(0.0f) {

	DLight light;
	light.direction = { -0.3f, -1.0f, -0.2f };
	light.intensity = 1.0f;
	light.color = { 1.0f, 1.0f, 0.0f };


	//ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui::StyleColorsDark();

	m_window = std::make_unique <Window>(instance);
	m_renderer = std::make_unique <Renderer>(m_window->getHandle());

	ImGui_ImplWin32_Init(m_window->getHandle());

	m_renderer->clearColor(0.0f, 0.0f, 0.0f, 1.0f);

	lightBuffer = new ConstantBuffer(&light, sizeof(light), ShaderType::pixelShader, 1);

}

void App::run() {

	Camera camera;
	
	auto cubeMesh = Mesh::cubeMesh();
	auto material = Material::createMaterial();

	CubeMeshed cube1(cubeMesh, material, &camera, lightBuffer);
	cube1.setColor(1.0f, 0.0f, 1.0f);

	CubeMeshed cube2(cubeMesh, material, &camera, lightBuffer);
	cube2.setColor(0.0f, 1.0f, 0.0f);

	while (m_window->isOpen()) {
		
		//deltatime and message handling
		this->update();

		//imgui init
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		//updating
		camera.update(m_deltaTime);
		cube1.update(m_deltaTime);
		cube2.update(m_deltaTime);

		//rendering
		this->render();
		cube2.render(m_renderer->m_context.Get());
		cube1.render(m_renderer->m_context.Get());

		//imgui render
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());


		//swap buffers
		m_renderer->flipBuffers();
	}
}

void App::update() {
	m_deltaTime = m_dtClock.elapsed();
	m_window->handleMessages();
}

void App::render() {
	m_renderer->wipeOff();
}

void App::imguiRender() {
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();	
}

App::~App() {
	delete lightBuffer;
}