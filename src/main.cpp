#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_FORCE_LEFT_HANDED
#define GLM_FORCE_ROW_MAJOR
#define WIN32_LEAN_AND_MEAN

#include <SDL_syswm.h>
#include <SDL.h>
#include <windows.h>

#include "Renderer.hpp"
#include "Vertex.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "InputLayout.hpp"
#include "Shader.hpp"


int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Not-Dx11", 100, 100, 1280, 720, 0);
    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(window, &wmInfo);
    HWND handle = wmInfo.info.win.window;    

    Renderer renderer(handle);

    bool open = true;
    SDL_Event e;

    Vertex vertices[] {
        {{-0.5f, -0.5f, 0.0f}},
        {{ 0.0f,  0.5f, 0.0f}},
        {{ 0.5f, -0.5f, 0.0f}}
    };
    
    uint32_t indices[] = {
        0, 1, 2
    };

    VertexBuffer vbo(vertices, 3, sizeof(Vertex));
    IndexBuffer ibo(indices, 3);
    Shader shader(L"Shader/VertexShader.hlsl", L"Shader/PixelShader.hlsl");
    InputLayout ilo(shader.blobs());
    ilo.addLayout({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 });
    ilo.createLayout();

    while(open) {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT)
                open = false;
        }
        
        renderer.clear();
        renderer.preRender();    
        
        vbo.bind();
        ibo.bind();
        shader.bind();
        ilo.bind();

        renderer.drawIndexed(ibo.indexCount());

        renderer.swap();
    }


    SDL_DestroyWindow(window);
    SDL_Quit();
}