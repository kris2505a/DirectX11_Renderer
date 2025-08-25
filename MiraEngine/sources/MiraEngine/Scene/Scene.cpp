#include <MiraPreCompHeader.h>
#include "Scene.h"

namespace Mira {


Scene::Scene(MiraId _sceneId, const std::string& _name)
	: m_sceneId(_sceneId), m_name(_name){

}

void Scene::update(float deltaTime) {
	for (auto& entity : m_entities) {
		entity->update(deltaTime);
	}
	for (auto& comp : m_cameraComponents) {
		comp->update();
	}
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

void Scene::init() {
	for (auto& entity : m_entities) {
		entity->construct();
		entity->init();
	}
}

std::vector<Entity*>& Scene::getEntities() {
	return m_entities;
}

MiraId Scene::getId() const {
	return m_sceneId;
}

const std::string& Scene::getName() const {
	return m_name;
}

Entity* Scene::getEntityById(MiraId id) const {
	for (auto* iter : m_entities) {
		if (iter->m_entityId == id) {
			return iter;
		}
	}
	return nullptr;
}

template<>
CameraComponent* Scene::createComponent(MiraId id) {
	auto* cam = new CameraComponent;
	m_cameraComponents.push_back(cam);
	auto* ent = getEntityById(id);
	MIRA_ASSERT(ent, "Unable to find entity");
	ent->p_camera = cam;
	return cam;
}

template<>
RigidBodyComponent* Scene::createComponent(MiraId id) {
	auto owner = getEntityById(id);
	MIRA_ASSERT(owner, "Unable to find Entity");
	auto* rb = new RigidBodyComponent;
	rb->owner = owner;
	owner->p_rigidBody = rb;
	return rb;
}

Scene::~Scene() {

	for (auto* iter : m_entities) {
		if (iter) delete iter;
	}
	for (auto* iter : m_transformComponents) {
		if (iter) delete iter;
	}
	for (auto* iter : m_cameraComponents) {
		if (iter) delete iter;
	}
	for (auto* iter : m_rigidBodyComponents) {
		if (iter) delete iter;
	}
	m_entities.clear();
	m_transformComponents.clear();
	m_cameraComponents.clear();
	m_rigidBodyComponents.clear();
}

}//namespace ends