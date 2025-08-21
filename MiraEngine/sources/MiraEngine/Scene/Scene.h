#pragma once
#include <MiraEngine/Core/MiraCore.h>
#include <MiraEngine/Entity/Entity.h>
#include <MiraEngine/Renderer/Renderer.h>
#include <MiraEngine/Entity/Components.h>
#include <memory>
#include <vector>

namespace Mira {

class MIRA_API Scene {

public:
	Scene(uint32_t _sceneId = 0, const std::string& _name = "Scene");
	~Scene();
	void update(float deltaTime);
	void render(Renderer* renderer);
	virtual void handleInput(float deltaTime);
	std::vector<Entity*>& getEntities();
	
	template <typename T> 
	void createEntity() {
		Entity* ent = new T;
		ent->p_scene = this;
		ent->m_entityId = m_entityIdGenerator++;
		m_entities.push_back(ent);
		m_transformComponents[ent->m_entityId] = TransformComponent();
	}

	uint32_t getId() const;
	const std::string& getName() const;

protected:
	std::vector<Entity*> m_entities;

private:
	uint32_t m_sceneId;
	std::string m_name;
	static uint32_t m_entityIdGenerator;
	std::unordered_map <uint32_t, TransformComponent> m_transformComponents;
};

}//namespace ends