#include <MiraPreCompHeader.h>
#include "Renderer.h"
#include <MiraEngine/Core/MiraMacros.h>

namespace Mira {

Renderer::Renderer(sf::RenderWindow* _window)
	: m_renderer(nullptr) {

	m_renderer = _window;
}

void Renderer::render(sf::Drawable& drawable) {
	m_renderer->draw(drawable);
}


Renderer::~Renderer() {
	
}

void Renderer::clear(int r, int g, int b, int a) {
	m_renderer->clear(sf::Color(r, g, b, a));
}

void Renderer::renderBinded() {
	m_renderer->display();
}

sf::RenderWindow* Renderer::getRenderer() const {
	return m_renderer;
}

}