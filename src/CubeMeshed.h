#pragma once
#include "Mesh.h"
#include "Material.h"
#include "Transform.h"
#include "Camera.h"

class CubeMeshed {

public:
	CubeMeshed(Mesh* mesh, Material* mat, Camera* cam);
	~CubeMeshed();
	void setColor(float r, float g, float b) {
		m_color.x = r;
		m_color.y = g;
		m_color.z = b;
		m_pcbo->update(&m_color, sizeof(m_color));
	}
	
	void update(float deltaTime);
	void render(ID3D11DeviceContext* context);

private:
	Mesh* p_mesh;
	Material* p_material;
	Transform* m_transform;
	Camera* p_camera;
	ConstantBuffer* m_vcbo;
	ConstantBuffer* m_pcbo;
	dx::XMFLOAT4 m_color;
};