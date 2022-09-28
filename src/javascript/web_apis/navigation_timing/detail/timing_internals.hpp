#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_NAVIGATION_TIMING_DETAIL_TIMING_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_NAVIGATION_TIMING_DETAIL_TIMING_INTERNALS_HPP

#include "ext/number.hpp"
#include "ext/optional.hpp"
#include INCLUDE_INNER_TYPES(fetch)
#include INCLUDE_INNER_TYPES(resource_timing)
#include INCLUDE_INNER_TYPES(service_workers)
namespace dom::nodes {class document;}

namespace navigation_timing::detail
{
    auto create_navigation_timing_entry(
            dom::nodes::document* document,
            fetch::detail::fetch_timing_info_t&& fetch_timing,
            ext::number<ushort> redirect_count,
            ext::optional<service_workers::detail::service_worker_timing_info_t> service_worker_timing,
            resource_timing::detail::cache_mode_t cache_mode,
            fetch::detail::response_body_info_t&& body_info)
            -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_NAVIGATION_TIMING_DETAIL_TIMING_INTERNALS_HPP
