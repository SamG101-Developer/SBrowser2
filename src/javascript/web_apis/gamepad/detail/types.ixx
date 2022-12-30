module;
#include "ext/macros.hpp"


export module apis.gamepad.types;


DEFINE_FWD_DECL_NAMESPACE(gamepad)
{
    class gamepad;
    class gamepad_button;
    class gamepad_event;
}


DEFINE_FWD_DECL_NAMESPACE_DETAIL(gamepad)
{
    enum class gamepad_mapping_type_t {_, STANDARD, XR_STANDARD};
}
