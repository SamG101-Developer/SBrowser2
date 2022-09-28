#include "timing_internals.hpp"

#include "dom/nodes/document.hpp"

#include "fetch/_typedefs.hpp"
#include "fetch/detail/body_internals.hpp"
#include "fetch/detail/fetch_internals.hpp"
#include "fetch/detail/response_internals.hpp"

#include "navigation_timing/performance_navigation_timing.hpp"
#include "resource_timing/detail/resource_timing_internals.hpp"
#include "service_workers/detail/service_worker_internals.hpp"
#include "url/detail/url_internals.hpp"


auto navigation_timing::detail::create_navigation_timing_entry(
        dom::nodes::document* document,
        fetch::detail::fetch_timing_info_t&& fetch_timing,
        ext::number<ushort> redirect_count,
        ext::optional<service_workers::detail::service_worker_timing_info_t> service_worker_timing,
        resource_timing::detail::cache_mode_t cache_mode,
        fetch::detail::response_body_info_t&& body_info) -> void
{
    auto navigation_timing_entry = performance_navigation_timing{};
    resource_timing::detail::setup_resource_timing_entry(
            &navigation_timing_entry,
            fetch::detail::initiator_type_t::NAVIGATION,
            url::detail::url_serializer(*document->d_func()->url),
            std::move(fetch_timing),
            cache_mode,
            std::move(body_info));

    // TODO
}
