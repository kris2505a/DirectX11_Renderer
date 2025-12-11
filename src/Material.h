#pragma once
#include "Shader.h"
#include "InputLayout.h"
#include "Texture.h"

class Material {
	friend class CubeMeshed;
public:
	Material() = default;
	~Material();

	static Material* createMaterial();

private:
	InputLayout* m_ilo;
	Shader* m_shader;
};