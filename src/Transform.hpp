#pragma once
#include "DirectXMath.h"

#define rad(x) DirectX::XMConvertToRadians(x)

namespace dx = DirectX;

struct Transform {
    dx::XMFLOAT3 position{0.0f, 0.0f, 0.0f};
    dx::XMFLOAT3 rotation{0.0f, 0.0f, 0.0f};
    dx::XMFLOAT3 scale{1.0f, 1.0f, 1.0f};

    dx::XMMATRIX model() {
        return dx::XMMatrixScaling(scale.x, scale.y, scale.z) *
               dx::XMMatrixRotationRollPitchYaw(rad(rotation.x), rad(rotation.y), rad(rotation.z)) *
               dx::XMMatrixTranslation(position.x, position.y, position.z);
    }
};