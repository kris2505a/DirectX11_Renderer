#include "GameApp.hpp"
#include <iostream>

namespace Mira {

GameApp::GameApp() {
    
}

void GameApp::run() {
    while (true) {
        this->update();
        this->render();   
    }
}

void GameApp::update() {
    std::cout << "Updating!  -->  ";
}

void GameApp::render() {
    std::cout << "Rendering!\n";
}

void GameApp::handleInput() {

}

}//namespace ends