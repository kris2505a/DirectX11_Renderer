#include <MiraPreCompHeader.h>
#include "Layer.h"


namespace Mira {

uint32_t Layer::s_idGenerator = 0;

void Layer::onAttach() {
	m_scenes.push_back(std::make_unique<Scene>(s_idGenerator++, "Mira Scene"));
}

void Layer::onDetach() {
	
}

Scene* Layer::getCurrentScene() const {
	return m_scenes.at(m_currentSceneIndex).get();
	//return nullptr;
}

void Layer::loadScene(int sceneIndex) {
	m_currentSceneIndex = sceneIndex;
}

void Layer::onUpdate(float deltaTime) {
	MIRA_ASSERT(m_currentSceneIndex < m_scenes.size(), "Scene Index out of range")
	m_scenes.at(m_currentSceneIndex)->handleInput(deltaTime);
	m_scenes.at(m_currentSceneIndex)->update(deltaTime);
}

void Layer::onRender(Renderer* renderer) {
	m_scenes.at(m_currentSceneIndex)->render(renderer);
}

void Layer::onEvent(Event& e) {
	if (e.getType() == EventType::windowClose)
		MIRA_LOG(INFO, "Window Close");
}



} //namespace ends