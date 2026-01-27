#pragma once
#include <wrl/client.h>
#include <d3dcompiler.h>

namespace dxr {

struct Blobs {
	Microsoft::WRL::ComPtr <ID3DBlob> vsBlob;
	Microsoft::WRL::ComPtr <ID3DBlob> psBlob;
};

}