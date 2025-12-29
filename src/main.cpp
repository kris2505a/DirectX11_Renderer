#include <SDL_syswm.h>
#include <SDL.h>
#include <windows.h>
#include <iostream>

#include "Renderer.hpp"
#include "InputLayout.hpp"
#include "Shader.hpp"

#include "DbgCube.hpp"

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

   

    DbgCube cube;
    cube.transform()->position.x = 0.5f;
    cube.transform()->position.z = 2.0f;
    cube.color = { 1.0f, 0.0f, 0.0f, 1.0f };

    DbgCube cube2;
    cube2.transform()->position.x = 0.0f;
    cube2.color = { 0.0f, 1.0f, 0.0f, 1.0f };

    while(open) {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT)
                open = false;
        }
        
        renderer.clear();
        renderer.preRender();    
        
        cube.update(1.0f);
        cube2.update(1.0f);

        cube.render();
        cube2.render();

        renderer.swap();
    }


    SDL_DestroyWindow(window);
    SDL_Quit();
}