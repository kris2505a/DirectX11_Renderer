#pragma once
#include "Rendering/Shader.h"
#include "Rendering/InputLayout.h"
#include "Rendering/Texture.h"
#include <memory>
#include <DirectXMath.h>

enum class MaterialType {
	SolidColor,
	Texture
};

class Material {
	friend class Renderer;
public:
	Material() = default;
	~Material() = default;
	const DirectX::XMFLOAT4& getColor() const;
	void setColor(float r, float g, float b, float a);
	static std::unique_ptr <Material> createSolidMaterial();
	void bind() const;
	void setTexture(const std::string& path);

private:
	std::weak_ptr <class MaterialSharedStates> m_sharedState;
	std::unique_ptr <Texture> m_texture;
	MaterialType m_type;
	DirectX::XMFLOAT4 m_color;
};

class MaterialSharedStates {
	friend class Material;
private:

	std::unique_ptr <Shader> m_shader;
	std::unique_ptr <InputLayout> m_ilo;

	static std::shared_ptr <MaterialSharedStates> s_sharedInstance;
};