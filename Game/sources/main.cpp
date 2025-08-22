#include <MiraEngine.h>

class Player : public Mira::Entity {
public:
	virtual void update(float deltatime) {

	}
	virtual void render(Mira::Renderer* renderer) {
		renderer->getRenderer()->draw(m_sprite);
	}
	virtual void handleInput(float deltaTime) {

	}

	Player() {
		auto texture = m_texture.loadFromFile("textures/player.png");
		MIRA_ASSERT(texture, "Unable to load Texture");
		m_sprite.setTexture(m_texture);
	}
	~Player() = default;

private:
	sf::Sprite m_sprite;
	sf::Texture m_texture;
};

class World : public Mira::Scene {
public:
	World() = default;
	~World() = default;
};

class GameLayer : public Mira::Layer {
public:
	GameLayer() {
		m_scenes.push_back(std::make_unique <World>());
		getCurrentScene()->createEntity<Player>();
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