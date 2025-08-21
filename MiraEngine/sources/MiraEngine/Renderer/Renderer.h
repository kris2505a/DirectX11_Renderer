#pragma once
#include <MiraEngine/Core/MiraCore.h>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Drawable.hpp>

namespace Mira {

class MIRA_API Renderer {
public:
	Renderer(sf::RenderWindow* _window);
	~Renderer();
	void clear(int r = 0u, int g = 0u, int b = 0u, int a = 0u);
	void renderBinded();
	sf::RenderWindow* getRenderer() const;
	void render(sf::Drawable& drawable);

private:
	sf::RenderWindow* m_renderer;

};

} //namespace ends