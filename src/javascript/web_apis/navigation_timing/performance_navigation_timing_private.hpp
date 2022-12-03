#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_NAVIGATION_TIMING_PERFORMANCE_NAVIGATION_TIMING_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_NAVIGATION_TIMING_PERFORMANCE_NAVIGATION_TIMING_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "resource_timing/performance_resource_timing_private.hpp"

#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(navigation_timing)
#include INCLUDE_INNER_TYPES(service_workers)


DEFINE_PRIVATE_CLASS(navigation_timing, performance_navigation_timing) : resource_timing::performance_resource_timing_private
{
    std::unique_ptr<html::detail::document_load_timing_info_t> document_load_timing;
    std::unique_ptr<html::detail::document_unload_timing_info_t> previous_document_unload_timing;
    std::unique_ptr<service_workers::detail::service_worker_timing_info_t> service_worker_timing_info;
    ext::number<ushort> redirect_count;
    detail::navigation_timing_type_t navigation_type;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_NAVIGATION_TIMING_PERFORMANCE_NAVIGATION_TIMING_PRIVATE_HPP
