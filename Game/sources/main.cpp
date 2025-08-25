#include <MiraEngine.h>

class Player : public Mira::Entity {
public:

	virtual void construct() {
		m_camera = p_scene->createComponent <Mira::CameraComponent>(getCurrentId());
	}

	virtual void init() {
		
	}
	virtual void update(float deltatime) {

	}
	virtual void render(Mira::Renderer* renderer) {
		renderer->getRenderer()->draw(m_sprite);
	}
	virtual void handleInput(float deltaTime) {
		if (Mira::Input::isKeyPressed(sf::Keyboard::Left)) {
			m_camera->position.x -= 5000 * deltaTime;
		}
		if (Mira::Input::isKeyPressed(sf::Keyboard::Right)) {
			m_camera->position.x += 5000 * deltaTime;
		}

	}

	Player() {
		auto texture = m_texture.loadFromFile("textures/player.png");
		MIRA_ASSERT(texture, "Unable to load Texture");
		m_sprite.setTexture(m_texture);
		//auto rb = p_scene->createComponent <Mira::RigidBodyComponent>(m_entityId);
	}
	~Player() = default;

private:
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	Mira::CameraComponent* m_camera;
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