#pragma once
#include "Window.h"
#include "Renderer.h"
#include "Clock.h"

#include <memory>

class App {
public:
	App(HINSTANCE instance);
	~App() = default;
	void run();

private:
	void update();
	void render();
	void imguiRender();

private:
	std::unique_ptr <Window> m_window;
	std::unique_ptr <Renderer> m_renderer;
	
	Clock m_dtClock;
	float m_deltaTime;
};