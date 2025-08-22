#include <MiraEngine.h>

class World : public Mira::Scene {
public:
	World() = default;
	~World() = default;
};

class GameLayer : public Mira::Layer {
public:
	GameLayer() {
		m_scenes.push_back(std::make_unique <World>());
	}
	~GameLayer() = default;
};

class Game : public Mira::GameApp {
public:
	Game() {
		this->pushLayer(new GameLayer());
	}
};


Mira::GameApp* Mira::createGame() {
	return new Game();
}