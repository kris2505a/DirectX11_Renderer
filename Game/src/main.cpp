#include <Engine.hpp>

class Sandbox : public Mira::GameApp {
public:
	Sandbox() {}
	~Sandbox() = default;
};


Mira::GameApp* Mira::createGameApp() {
	return new Sandbox;
}