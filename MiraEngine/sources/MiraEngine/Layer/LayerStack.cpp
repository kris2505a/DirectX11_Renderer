#include <MiraPreCompHeader.h>
#include "LayerStack.h"
#include "Layer.h"

namespace Mira {

void LayerStack::pushLayer(Layer* layer) {
	m_layers.emplace(m_layers.begin() + m_layerIndex, layer);
	m_layerIndex++;
	layer->onAttach();
}

void LayerStack::pushOverlay(Layer* _overlay) {
	m_layers.emplace_back(_overlay);
	_overlay->onAttach();
}

void LayerStack::popLayer(Layer* layer) {
	auto llayer = std::find(m_layers.begin(), m_layers.end(), layer);
	if (llayer != m_layers.end()) {
		layer->onDetach();
		m_layers.erase(llayer);
		m_layerIndex--;
	}
}

void LayerStack::popOverlay(Layer* overlay) {
	auto layer = std::find(m_layers.begin(), m_layers.end(), overlay);
	if (layer != m_layers.end()) {
		overlay->onDetach();
		m_layers.erase(layer);
	}
}

LayerStack::~LayerStack() {
	for (auto& layer : m_layers)
		delete layer;
	m_layers.clear();
}

std::vector<Layer*>::iterator LayerStack::begin() {
	return m_layers.begin();
}
std::vector<Layer*>::iterator LayerStack::end() {
	return m_layers.end();
}

} //namespace ends