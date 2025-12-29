#include "DbgCube.hpp"
#include "Vertex.hpp"
#include <SDL_keyboard.h>
#include <SDL_keycode.h>

DbgCube::DbgCube() {
    
    Vertex vertices[] = {
        // ---------- FRONT (+Z) ----------
        {{-0.5f,  0.5f,  0.5f}}, // 0
        {{ 0.5f,  0.5f,  0.5f}}, // 1
        {{ 0.5f, -0.5f,  0.5f}}, // 2
        {{-0.5f, -0.5f,  0.5f}}, // 3

        // ---------- BACK (-Z) ----------
        {{ 0.5f,  0.5f, -0.5f}}, // 4
        {{-0.5f,  0.5f, -0.5f}}, // 5
        {{-0.5f, -0.5f, -0.5f}}, // 6
        {{ 0.5f, -0.5f, -0.5f}}, // 7

        // ---------- LEFT (-X) ----------
        {{-0.5f,  0.5f, -0.5f}}, // 8
        {{-0.5f,  0.5f,  0.5f}}, // 9
        {{-0.5f, -0.5f,  0.5f}}, //10
        {{-0.5f, -0.5f, -0.5f}}, //11

        // ---------- RIGHT (+X) ----------
        {{ 0.5f,  0.5f,  0.5f}}, //12
        {{ 0.5f,  0.5f, -0.5f}}, //13
        {{ 0.5f, -0.5f, -0.5f}}, //14
        {{ 0.5f, -0.5f,  0.5f}}, //15

        // ---------- TOP (+Y) ----------
        {{-0.5f,  0.5f, -0.5f}}, //16
        {{ 0.5f,  0.5f, -0.5f}}, //17
        {{ 0.5f,  0.5f,  0.5f}}, //18
        {{-0.5f,  0.5f,  0.5f}}, //19

        // ---------- BOTTOM (-Y) ----------
        {{-0.5f, -0.5f,  0.5f}}, //20
        {{ 0.5f, -0.5f,  0.5f}}, //21
        {{ 0.5f, -0.5f, -0.5f}}, //22
        {{-0.5f, -0.5f, -0.5f}}, //23
    };

    m_vbo = new VertexBuffer(vertices, std::size(vertices), sizeof(Vertex));

    uint32_t indices[] = {

        // FRONT (+Z)
         0,  1,  2,
         0,  2,  3,

        // BACK (-Z)
          4,  5,  6,
          4,  6,  7,

        // LEFT (-X)
           8,  9, 10,
           8, 10, 11,

        // RIGHT (+X)
           12, 13, 14,
           12, 14, 15,

        // TOP (+Y)
           16, 17, 18,
           16, 18, 19,

        // BOTTOM (-Y)
           20, 21, 22,
           20, 22, 23
    };

    m_ibo = new IndexBuffer(indices, std::size(indices));
    Entity::indexCount(std::size(indices));

    m_posSpeed = 0.05f;
    m_rotationSpeed = 0.05f;
}

void DbgCube::update(float deltaTime) {

    /*const Uint8* keys = SDL_GetKeyboardState(nullptr);

    if (keys[SDL_SCANCODE_W]) {
        m_transform.position.z += m_posSpeed;
    }
    if (keys[SDL_SCANCODE_S]) {
        m_transform.position.z -= m_posSpeed;
    }
    if (keys[SDL_SCANCODE_D]) {
        m_transform.position.x += m_posSpeed;
    }
    if (keys[SDL_SCANCODE_A]) {
        m_transform.position.x -= m_posSpeed;
    }*/

}

void DbgCube::bind() {
    m_vbo->bind();
    m_ibo->bind();
}


DbgCube::~DbgCube() {
    delete m_vbo;
    delete m_ibo;
}

