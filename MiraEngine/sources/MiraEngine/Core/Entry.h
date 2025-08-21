#pragma once
#include "GameApp.h"

extern Mira::GameApp* Mira::createGame();

int main(int argc, char** argv) {
	Mira::GameApp* game = Mira::createGame();
	game->run();
	delete game;
}