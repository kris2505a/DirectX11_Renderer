#include "App.h"
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

#include "Cube.h"
#include "CubeMeshed.h"

App::App(HINSTANCE instance) : m_deltaTime(0.0f) {

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
}

void App::run() {

	Camera camera;
	
	auto cubeMesh = Mesh::cubeMesh();
	auto material = Material::createMaterial();

	CubeMeshed cube1(cubeMesh, material, &camera);
	cube1.setColor(1.0f, 0.0f, 1.0f);

	CubeMeshed cube2(cubeMesh, material, &camera);
	cube2.setColor(0.0f, 1.0f, 0.0f);

	while (m_window->isOpen()) {
		this->update();
		this->imguiRender();
		camera.update(m_deltaTime);
		cube1.update(m_deltaTime);
		this->render();

		cube1.render(m_renderer->m_context.Get());

		m_renderer->flipBuffers();
	}
}

void App::update() {
	m_deltaTime = m_dtClock.elapsed();
	m_window->handleMessages();
}

void App::render() {
	m_renderer->wipeOff();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void App::imguiRender() {
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	
}