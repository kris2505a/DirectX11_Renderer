#pragma once
#include <DirectXMath.h>

namespace dxr {

struct Vertex3 {
    DirectX::XMFLOAT2 position;
    DirectX::XMFLOAT2 normal;
    DirectX::XMFLOAT2 uv;
};

}