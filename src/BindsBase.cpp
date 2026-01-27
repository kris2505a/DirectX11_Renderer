#include "BindsBase.h"
#include "Renderer.h"

namespace dxr {

ID3D11Device* BindsBase::device() const {
    return Renderer::getDevice();
}

ID3D11DeviceContext* BindsBase::context() const {
    return Renderer::getContext();
}

}