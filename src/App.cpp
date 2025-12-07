#include "App.h"
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

#include "Cube.h"

App::App(HINSTANCE instance) : m_deltaTime(0.0f) {

	//ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui::StyleColorsDark();


	m_window = std::make_unique <Window>(instance);
	m_renderer = std::make_unique <Renderer>(m_window->getHandle());
	m_renderer->vSync(true);

	ImGui_ImplWin32_Init(m_window->getHandle());


	m_renderer->clearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void App::run() {

	Camera camera;
	Cube cube(&camera, -0.7f, 0.5f, 0.0f);
	Cube cube2(&camera, 1.0f, -0.5f, 0.0f);
	
	while (m_window->isOpen()) {
		this->update();
		this->imguiRender();
		camera.update(m_deltaTime);
		cube.update(m_deltaTime);
		cube2.update(m_deltaTime);
		this->render();
		cube.bind();
		m_renderer->indexedRender(cube.getIndexCount());
		cube.unbind();

		cube2.bind();
		m_renderer->indexedRender(cube2.getIndexCount());
		cube2.unbind();

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