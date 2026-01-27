#include "Mesh.h"
#include "Vertex.h"
#include <vector>

std::shared_ptr <MeshSharedState> MeshSharedState::s_cubeMesh;

void Mesh::bind() {
    if (auto mesh = m_sharedState.lock()) {
        mesh->m_vbo->bind();
        mesh->m_ibo->bind();
    }
}

unsigned int Mesh::getIndexCount() const {
    if (auto mesh = m_sharedState.lock()) {
        return mesh->m_ibo->indexCount();
    }
    return 0;
}

std::unique_ptr<Mesh> Mesh::createCubeMesh() {
	auto mesh = std::make_unique <Mesh>();
	
	if (MeshSharedState::s_cubeMesh) {
		mesh->m_sharedState = MeshSharedState::s_cubeMesh;
        return mesh;
	}

	MeshSharedState::s_cubeMesh = std::make_shared <MeshSharedState>();

    std::vector<Vertex> vertices = {

        // +Z (Front)
        {{-0.5f, -0.5f,  0.5f}, {0, 0, 1}, {0, 1}},
        {{-0.5f,  0.5f,  0.5f}, {0, 0, 1}, {0, 0}},
        {{ 0.5f,  0.5f,  0.5f}, {0, 0, 1}, {1, 0}},
        {{ 0.5f, -0.5f,  0.5f}, {0, 0, 1}, {1, 1}},

        // -Z (Back)
        {{ 0.5f, -0.5f, -0.5f}, {0, 0, -1}, {0, 1}},
        {{ 0.5f,  0.5f, -0.5f}, {0, 0, -1}, {0, 0}},
        {{-0.5f,  0.5f, -0.5f}, {0, 0, -1}, {1, 0}},
        {{-0.5f, -0.5f, -0.5f}, {0, 0, -1}, {1, 1}},

        // +X (Right)
        {{ 0.5f, -0.5f,  0.5f}, {1, 0, 0}, {0, 1}},
        {{ 0.5f,  0.5f,  0.5f}, {1, 0, 0}, {0, 0}},
        {{ 0.5f,  0.5f, -0.5f}, {1, 0, 0}, {1, 0}},
        {{ 0.5f, -0.5f, -0.5f}, {1, 0, 0}, {1, 1}},

        // -X (Left)
        {{-0.5f, -0.5f, -0.5f}, {-1, 0, 0}, {0, 1}},
        {{-0.5f,  0.5f, -0.5f}, {-1, 0, 0}, {0, 0}},
        {{-0.5f,  0.5f,  0.5f}, {-1, 0, 0}, {1, 0}},
        {{-0.5f, -0.5f,  0.5f}, {-1, 0, 0}, {1, 1}},

        // +Y (Top)
        {{-0.5f,  0.5f,  0.5f}, {0, 1, 0}, {0, 1}},
        {{-0.5f,  0.5f, -0.5f}, {0, 1, 0}, {0, 0}},
        {{ 0.5f,  0.5f, -0.5f}, {0, 1, 0}, {1, 0}},
        {{ 0.5f,  0.5f,  0.5f}, {0, 1, 0}, {1, 1}},

        // -Y (Bottom)
        {{-0.5f, -0.5f, -0.5f}, {0, -1, 0}, {0, 1}},
        {{-0.5f, -0.5f,  0.5f}, {0, -1, 0}, {0, 0}},
        {{ 0.5f, -0.5f,  0.5f}, {0, -1, 0}, {1, 0}},
        {{ 0.5f, -0.5f, -0.5f}, {0, -1, 0}, {1, 1}},
    };

    MeshSharedState::s_cubeMesh->m_vbo = std::make_unique <VertexBuffer>(
        vertices.data(),
        static_cast <unsigned int> (vertices.size()),
        sizeof(Vertex)
    );

    std::vector<uint32_t> indices = {
         0,  1,  2,   0,  2,  3,   // Front
         4,  5,  6,   4,  6,  7,   // Back
         8,  9, 10,   8, 10, 11,   // Right
        12, 13, 14,  12, 14, 15,   // Left
        16, 17, 18,  16, 18, 19,   // Top
        20, 21, 22,  20, 22, 23    // Bottom
    };

    MeshSharedState::s_cubeMesh->m_ibo = std::make_unique <IndexBuffer>(
        indices.data(),
        static_cast <unsigned int> (indices.size())
    );

    mesh->m_sharedState = MeshSharedState::s_cubeMesh;
    return mesh;
}

