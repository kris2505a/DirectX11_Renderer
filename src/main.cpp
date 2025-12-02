#include "Window.h"
#include "Renderer.h"
#include "ErrorH.h"
#include "Cube.h"

#include <chrono>


int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd
) {

	Window* window = new Window(hInstance);
	Renderer* renderer = new Renderer(window->getHandle());
	renderer->vSync(false);

	renderer->clearColor(0.0f, 0.0f, 0.0f, 1.0f);

	Cube cube;

	auto previousTime = std::chrono::high_resolution_clock::now();

	while (window->isOpen()) {
		
		//deltatime
		auto currentTime = std::chrono::high_resolution_clock::now();

		// Calculate deltaTime in seconds
		std::chrono::duration<float> elapsed = currentTime - previousTime;
		float deltaTime = elapsed.count(); // deltaTime in seconds

		// Update previous time
		previousTime = currentTime;

		
		window->handleMessages();
		cube.update(deltaTime);
		renderer->wipeOff();

		cube.bindall();
		
		renderer->indexedRender(cube.getIndexCount());
		cube.unbindall();

		renderer->flipBuffers();


	}

	delete renderer;
	delete window;
}