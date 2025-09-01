#pragma once

#define NUVIO_NAMESPACE_BEGIN namespace nuvio {
#define NUVIO_NAMESPACE_END }

#define NUVIO_UI_NAMESPACE_BEGIN namespace nuvio { namespace ui {
#define NUVIO_UI_NAMESPACE_END } }

#define UNUSED(x) (void)(x)

#define REGISTER_COMPONENT(fn) \
    static ComponentAutoRegister _autoReg_##fn(fn());
