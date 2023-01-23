module;
#include "ext/macros.hpp"


export module apis.navigation_timing.types;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(navigation_timing)
{
    enum class navigation_timing_type_t {NAVIGATE, RELOAD, BACK_FORWARD, PRERENDER};
}
