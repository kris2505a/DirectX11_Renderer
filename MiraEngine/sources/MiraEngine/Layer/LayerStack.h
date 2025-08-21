#pragma once
#include <MiraEngine/Core/MiraCore.h>
#include <vector>

namespace Mira {

class MIRA_API LayerStack {
public:
	void pushLayer(class Layer* layer);
	void pushOverlay(class Layer* overlay);
	void popLayer(class Layer* layer);
	void popOverlay(class Layer* overlay);

	LayerStack() = default;
	~LayerStack();

	std::vector<class Layer*>::iterator begin();
	std::vector<class Layer*>::iterator end();


private:
	std::vector <Layer*> m_layers;
	unsigned int m_layerIndex = 0;

};

} //Namespace ends