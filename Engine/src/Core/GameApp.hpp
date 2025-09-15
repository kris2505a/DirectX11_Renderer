#pragma once
#include "Core.hpp"

namespace Mira {

class MIRA_API GameApp {
public:
    GameApp();
    ~GameApp() = default;

    void run();

private:
    void render();
    void update();
    void handleInput();

private:
    
};

GameApp* createGameApp();

} //namespace ends