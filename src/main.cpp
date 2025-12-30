#include <SDL_syswm.h>
#include <SDL.h>
#include <windows.h>
#include <iostream>

#include "Renderer.hpp"
#include "InputLayout.hpp"
#include "Shader.hpp"

#include "Sphere.hpp"

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Not-Dx11", 100, 100, 1280, 720, SDL_WINDOW_SHOWN);
    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(window, &wmInfo);
    HWND handle = wmInfo.info.win.window;    

    Renderer renderer(handle);

    bool open = true;
    SDL_Event e;
    
    Sphere sphere;

    while(open) {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT)
                open = false;
        }
        
        renderer.clear();
        renderer.preRender();    
        
        sphere.update(1.0f);
        sphere.render();

        renderer.swap();
    }


    SDL_DestroyWindow(window);
    SDL_Quit();
}