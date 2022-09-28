#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_RESOURCE_TIMING_PERFORMANCE_RESOURCE_TIMING_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_RESOURCE_TIMING_PERFORMANCE_RESOURCE_TIMING_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "performance_timeline/performance_entry_private.hpp"

#include INCLUDE_INNER_TYPES(fetch)
#include INCLUDE_INNER_TYPES(resource_timing)


DEFINE_PRIVATE_CLASS(resource_timing, performance_resource_timing) : performance_timeline::performance_entry_private
{
    ext::string requested_url;
    detail::cache_mode_t cache_mode;
    fetch::detail::initiator_type_t initiator_type;
    std::unique_ptr<fetch::detail::fetch_timing_info_t> timing_info;
    std::unique_ptr<fetch::detail::response_body_info_t> resource_info;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_RESOURCE_TIMING_PERFORMANCE_RESOURCE_TIMING_PRIVATE_HPP
