module;
#include "ext/macros.hpp"
#include <tl/expected.hpp>


export module apis.server_timing.detail;
import ext.core;


DEFINE_FWD_DECL_NAMESPACE(server_timing)
{
    class performance_server_timing;
}


DEFINE_FWD_DECL_NAMESPACE_DETAIL(server_timing)
{
    auto parse_server_timing_header_field(ext::string field) -> ext::expected<performance_server_timing>;
}
