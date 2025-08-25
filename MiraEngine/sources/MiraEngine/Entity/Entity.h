#pragma once
#include <MiraEngine/Core/MiraCore.h>
#include <MiraEngine/Core/MiraMacros.h>
#include <MiraEngine/Renderer/Renderer.h>
#include <SFML/Graphics.hpp>
#include <MiraEngine/Math/Vector.h>

namespace Mira {

class MIRA_API Entity {

	friend class Scene;
public:
	Entity();
	~Entity() = default;
	
	Vec2Df& getWorldPosition();

	inline MiraId getCurrentId() const { return m_entityId; }

protected:
	virtual void init();
	virtual void construct();
	virtual void update(float deltatime);
	virtual void render(Renderer* renderer);
	virtual void handleInput(float deltaTime);

	class Scene* p_scene;

private:
	MiraId m_entityId;
	struct TransformComponent* p_transform;
	struct CameraComponent* p_camera;
	struct RigidBodyComponent* p_rigidBody;
};

} //namespace ends