#include "BindsBase.h"
#include "Renderer.h"

ID3D11Device* BindsBase::device() const {
    return Renderer::getDevice();
}

ID3D11DeviceContext* BindsBase::context() const {
    return Renderer::getContext();
}