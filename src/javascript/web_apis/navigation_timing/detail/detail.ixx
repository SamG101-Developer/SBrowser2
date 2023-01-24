module;
#include "ext/macros.hpp"


export module apis.navigation_timing.detail;
import apis.dom.types;
import apis.fetch.types;
import apis.resource_timing.types;
import apis.service_workers.types;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(navigation_timing)
{
    auto create_navigation_timing_entry(
            dom::document* document, fetch::detail::fetch_timing_info_t&& fetch_timing, ext::number<ushort> redirect_count,
            ext::optional<service_workers::detail::service_worker_timing_info_t> service_worker_timing,
            resource_timing::detail::cache_mode_t cache_mode, fetch::detail::response_body_info_t&& body_info) -> void;
};
