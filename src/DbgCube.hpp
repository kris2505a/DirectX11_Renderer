#pragma once
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Entity.hpp"

class DbgCube : public Entity {
public:
    DbgCube();
    ~DbgCube();
    void update(float deltaTime) final override;
    void bind() final override;

private:
    VertexBuffer* m_vbo;
    IndexBuffer* m_ibo;

    float m_rotationSpeed;
    float m_posSpeed;
};