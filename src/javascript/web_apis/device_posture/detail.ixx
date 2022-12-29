module;
#include "ext/macros/pimpl.hpp"


export module apis.device_posture.detail;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(device_posture)
{
    auto update_device_posture() -> void;
    auto change() -> void;
    auto when_document_visible() -> void;
};
