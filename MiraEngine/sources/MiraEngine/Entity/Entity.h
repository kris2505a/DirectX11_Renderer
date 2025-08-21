#pragma once
#include <MiraEngine/Core/MiraCore.h>
#include <MiraEngine/Renderer/Renderer.h>
#include <SFML/Graphics.hpp>

namespace Mira {

class MIRA_API Entity {

	friend class Scene;
public:
	Entity();
	~Entity() = default;

	virtual void update(float deltatime);
	virtual void render(Renderer* renderer);
	virtual void handleInput(float deltaTime);

private:
	class Scene* p_scene;
	uint32_t m_entityId;
};

} //namespace ends