#include <MiraPreCompHeader.h>
#include "Input.h"
#include <MiraEngine/Core/MiraMacros.h>

namespace Mira {

bool Input::isKeyPressed(sf::Keyboard::Key _key) {
	return sf::Keyboard::isKeyPressed(_key);
}

bool Input::isButtonPressed(sf::Mouse::Button _button) {
	return sf::Mouse::isButtonPressed(_button);
}

Vec2Df Input::getMousePos() {
	auto pos = sf::Mouse::getPosition();
	return { (float)pos.x, (float)pos.y };
}

} // namespace Mira
