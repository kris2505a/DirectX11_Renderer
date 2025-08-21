#pragma once
#include <MiraEngine/Core/MiraCore.h>
#include <MiraEngine/Math/Vector.h>
#include <MiraEngine/Core/GameApp.h>

namespace Mira {

struct MIRA_API TransformComponent {
	Vec2Df position;
	float rotation;
	Vec2Df scale;
	TransformComponent(const Vec2Df& _position = {0.0f, 0.0f}, float _rotation = 0.0f, const Vec2Df& _scale = {0.0f, 0.0f}) 
		: position(_position), rotation(_rotation), scale(_scale) { }
};

struct MIRA_API CameraComponent {
	Vec2Df position;
	Vec2Df size;	
	float zoom;
	sf::View camera;
	CameraComponent(const Vec2Df& _position = {0.0f, 0.0f}, const Vec2Df& _size = {100.f, 100.f}, float _zoom = 1.0f) 
		: position(_position), size(_size), zoom(_zoom) {
		camera.setSize(size);
		camera.setCenter(position);
		camera.zoom(zoom);
	}
};

} //namespace ends