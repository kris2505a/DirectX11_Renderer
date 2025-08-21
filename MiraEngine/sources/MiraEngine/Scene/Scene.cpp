#include <MiraPreCompHeader.h>
#include "Scene.h"

namespace Mira {

uint32_t Scene::m_entityIdGenerator = 0;


Scene::Scene(uint32_t _sceneId, const std::string& _name)
	: m_sceneId(_sceneId), m_name(_name){

}


void Scene::update(float deltaTime) {
	for (auto& entity : m_entities)
		entity->update(deltaTime);
}

void Scene::render(Renderer* renderer) {
	for (auto& entity : m_entities)
		entity->render(renderer);
}

void Scene::handleInput(float deltaTime) {
	for (auto& entity : m_entities) {
		entity->handleInput(deltaTime);
	}
}

std::vector<Entity*>& Scene::getEntities() {
	return m_entities;
}

uint32_t Scene::getId() const {
	return m_sceneId;
}

const std::string& Scene::getName() const {
	return m_name;
}

Scene::~Scene() {

	for (auto* iter : m_entities) {
		if (iter)
			delete iter;
	}
	m_entities.clear();
	m_transformComponents.clear();
}

}//namespace ends