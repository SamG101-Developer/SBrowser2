module;
#include "ext/macros/pimpl.hpp"


export module apis.resource_timing.detail;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(resource_timing)
{
    enum class cache_mode_t {_, LOCAL, VALIDATED};
}
