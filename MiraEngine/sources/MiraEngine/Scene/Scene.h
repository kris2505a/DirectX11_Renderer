#pragma once
#include <MiraEngine/Core/MiraCore.h>
#include <MiraEngine/Entity/Entity.h>
#include <MiraEngine/Renderer/Renderer.h>
#include <MiraEngine/Entity/Components.h>
#include <MiraEngine/Core/MiraMacros.h>
#include <memory>
#include <vector>

namespace Mira {

class MIRA_API Scene {

public:
	Scene(MiraId _sceneId = 0, const std::string& _name = "Scene");
	~Scene();
	void init();
	void update(float deltaTime);
	void render(Renderer* renderer);
	virtual void handleInput(float deltaTime);
	std::vector<Entity*>& getEntities();
	
	template <typename T> 
	inline T* createEntity() {
		T* ent = new T;
		ent->Entity::p_scene = this;
		m_entityIdGenerator++;
		ent->m_entityId = m_entityIdGenerator;
		
		auto* transform = new TransformComponent;
		m_transformComponents.push_back(transform);
		ent->p_transform = transform;
		m_entities.push_back(ent);

		return ent;
	}

	MiraId getId() const;
	const std::string& getName() const;
	
	Entity* getEntityById(MiraId id) const;


public:
	template <typename T>
	inline T* createComponent(MiraId id) {
		static_assert (false);
	}

	template<>
	CameraComponent* createComponent(MiraId id);
	template<>
	RigidBodyComponent* createComponent(MiraId id);

protected:
	std::vector<Entity*> m_entities;

private:
	MiraId m_sceneId;
	std::string m_name;
	MiraId m_entityIdGenerator = 0;
	std::vector <TransformComponent*> m_transformComponents;
	std::vector <CameraComponent*> m_cameraComponents;
	std::vector <RigidBodyComponent*> m_rigidBodyComponents;

	
};

}//namespace ends