#pragma once
#include "MiraCore.h"
#include <MiraEngine/Window/Window.h>
#include <MiraEngine/Renderer/Renderer.h>
#include <MiraEngine/Layer/LayerStack.h>
#include <memory>
#include <MiraEngine/Clock/Clock.h>

#include <SFML/Graphics.hpp>

namespace Mira {
class MIRA_API GameApp {
public:
	GameApp();
	virtual ~GameApp();
	void run();
	void render();
	virtual void update();
	void onEvent(Event& e);
	void pushLayer(Layer* layer);
	void pushOverlay(Layer* overlay);
	Renderer* getRenderer() const;
	static GameApp* getInstance();
	Window* getWindow() const;

private:
	static GameApp* s_instance;

	std::unique_ptr <Window> m_window;
	//std::unique_ptr <Renderer> m_renderer;
	Renderer* m_renderer;
	LayerStack m_layers;
	Clock m_clock;
	float m_deltaTime;
};

GameApp* createGame();

} //Namespace Ends
