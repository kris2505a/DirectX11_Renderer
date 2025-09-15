#include "GameApp.hpp"

extern Mira::GameApp* Mira::createGameApp();

int main(int argc, char** argv) {

    Mira::GameApp* app = Mira::createGameApp();
    app->run();
    delete app;
    return 0;

}