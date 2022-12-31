module;
#include "ext/macros.hpp"


export module apis.resource_timing.performance_resource_timing:p;
import apis.performance_timeline.performance_entry;

IMPORT_ALL_TYPES(fetch);
IMPORT_ALL_TYPES(resource_timing);


DEFINE_PRIVATE_CLASS(resource_timing, performance_resource_timing)
        : performance_timeline::performance_entry_private
{
public:
    MAKE_QIMPL(performance_resource_timing);

public:
    ext::string requested_url;
    detail::cache_mode_t cache_mode;
    fetch::detail::initiator_type_t initiator_type;
    std::unique_ptr<fetch::detail::fetch_timing_info_t> timing_info;
    std::unique_ptr<fetch::detail::response_body_info_t> resource_info;
};
