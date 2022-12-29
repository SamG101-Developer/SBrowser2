module;
#include "ext/macros/macros.hpp"


export module apis.device_posture.types;


DEFINE_FWD_DECL_NAMESPACE(device_posture)
{
    class device_posture;
}


DEFINE_FWD_DECL_NAMESPACE_DETAIL(device_posture)
{
    enum device_posture_type_t {CONTINUOUS, FOLDED, FOLDED_OVER};
}
