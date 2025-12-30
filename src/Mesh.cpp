#include "Mesh.hpp"
#include "Vertex.hpp"
#include <DirectXMath.h>
#include <vector>

std::shared_ptr <Mesh> Mesh::s_cubeMesh = nullptr;
std::shared_ptr <Mesh> Mesh::s_sphereMesh = nullptr;

std::shared_ptr <Mesh> Mesh::cubeMesh() {

    if (s_cubeMesh)
        return s_cubeMesh;

    s_cubeMesh = std::shared_ptr <Mesh>(new Mesh());
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

    s_cubeMesh->m_vbo = std::make_unique <VertexBuffer>(vertices, std::size(vertices), sizeof(Vertex));
    s_cubeMesh->m_ibo = std::make_unique <IndexBuffer>(indices, std::size(indices));


    return s_cubeMesh;
}

std::shared_ptr <Mesh> Mesh::sphereMesh() {
    if (s_sphereMesh)
        return s_sphereMesh;

    s_sphereMesh = std::shared_ptr <Mesh>(new Mesh());

    int stack = 16;
    int slice = 32;

    float dPhi = DirectX::XM_PI / stack;
    float dTheta = 2 * DirectX::XM_PI / slice;

    std::vector <Vertex> vertices;

    for (int i = 0; i <= stack; i++) {
        float phi = i * dPhi;
        
        for (int j = 0; j <= slice; j++) {
            float theta = j * dTheta;

            float x = 0.5f * sinf(phi) * cosf(theta);
            float y = 0.5f * cosf(phi);
            float z = 0.5f * sinf(phi) * sinf(theta);

            vertices.push_back({{ x, y, z }});
        }
    }

    s_sphereMesh->m_vbo = std::make_unique <VertexBuffer>(vertices.data(), vertices.size(), sizeof(Vertex));

    int ring = slice + 1;

    std::vector <uint32_t> indices;
    for (int i = 0; i < stack; i++) {
        for (int j = 0; j < slice; j++) {
            uint32_t a = i * ring + j;
            uint32_t b = (i + 1) * ring + j;
            uint32_t c = (i + 1) * ring + (j + 1);
            uint32_t d = i * ring + (j + 1);

            indices.push_back(a);
            indices.push_back(b);
            indices.push_back(c);

            indices.push_back(a);
            indices.push_back(c);
            indices.push_back(d);
        }
    }
    s_sphereMesh->m_ibo = std::make_unique<IndexBuffer>(indices.data(), indices.size());
    return s_sphereMesh;
}

void Mesh::bind() const {
    m_vbo->bind();
    m_ibo->bind();
}

unsigned int Mesh::indexCount() const {
    return m_ibo->indexCount();
}

