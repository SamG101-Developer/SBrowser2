module;
#include "ext/macros/pimpl.hpp"


export module apis.resource_timing.performance_resource_timing_private;
import apis.performance_timeline.performance_entry_private;

import apis.resource_timing.types;
import apis.fetch.types;
import ext.core;


DEFINE_PRIVATE_CLASS(resource_timing, performance_resource_timing)
        : performance_timeline::performance_entry_private
{
    ext::string requested_url;
    detail::cache_mode_t cache_mode;
    fetch::detail::initiator_type_t initiator_type;
    std::unique_ptr<fetch::detail::fetch_timing_info_t> timing_info;
    std::unique_ptr<fetch::detail::response_body_info_t> resource_info;
};
