module;
#include "ext/macros.hpp"


export module apis.navigation_timing.performance_navigation_timing:p;
import apis.resource_timing.performance_resource_timing;

import apis.html.types;
import apis.service_workers.types;
import apis.navigation_timing.types;


DEFINE_PRIVATE_CLASS(navigation_timing, performance_navigation_timing)
        : resource_timing::performance_resource_timing_private
{
public:
    MAKE_QIMPL(performance_navigation_timing);

public:
    std::unique_ptr<html::detail::document_load_timing_info_t> document_load_timing;
    std::unique_ptr<html::detail::document_unload_timing_info_t> previous_document_unload_timing;
    std::unique_ptr<service_workers::detail::service_worker_timing_info_t> service_worker_timing_info;
    ext::number<ushort> redirect_count;
    detail::navigation_timing_type_t navigation_type;
};
