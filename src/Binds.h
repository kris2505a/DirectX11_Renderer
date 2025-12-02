#pragma once
#include <d3d11.h>

class Binds {
public:
	virtual void bind() const = 0;
	virtual void unbind() const = 0;

protected:
	ID3D11Device* device() const;
	ID3D11DeviceContext* context() const;
	IDXGISwapChain* swapChain() const;
};