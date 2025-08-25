#include <MiraPreCompHeader.h>
#include "Entity.h"
#include <MiraEngine/Scene/Scene.h>
#include "Components.h"

namespace Mira {

Entity::Entity() : p_scene(nullptr), m_entityId(0) {

}

void Entity::construct() {

}

void Entity::init() {

}

void Entity::update(float deltaTime) {

}

void Entity::render(Renderer* renderer) {
	
}

void Entity::handleInput(float deltaTime) {

}

Vec2Df& Entity::getWorldPosition() {
	return this->p_transform->position;
}


} // namespace ends