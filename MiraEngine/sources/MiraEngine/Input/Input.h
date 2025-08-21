#pragma once
#include <MiraEngine/Core/MiraCore.h>
#include <MiraEngine/Math/Vector.h>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>


namespace Mira {
class MIRA_API Input {
public:

	Input() = delete;
	~Input() = delete;
	Input(const Input&) = delete;
	Input& operator=(const Input&) = delete;

	static bool isKeyPressed(sf::Keyboard::Key _key);	
	static bool isButtonPressed(sf::Mouse::Button _button);
	static Vec2Df getMousePos();

};

}