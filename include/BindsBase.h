#pragma once
#include <d3d11.h>
#include <wrl/client.h>


namespace wrl = Microsoft::WRL;

class BindsBase {
public:
    BindsBase() = default;
    ~BindsBase() = default;

    ID3D11Device* device() const;
    ID3D11DeviceContext* context() const;

    virtual void bind() const = 0;
};