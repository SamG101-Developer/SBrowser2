#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_NAVIGATION_TIMING_PERFORMANCE_NAVIGATION_TIMING_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_NAVIGATION_TIMING_PERFORMANCE_NAVIGATION_TIMING_HPP

#include "resource_timing/performance_resource_timing.hpp"
namespace navigation_timing {class performance_navigation_timing;}

#include <memory>
#include USE_INNER_TYPES(hr_time)
#include USE_INNER_TYPES(html)
#include USE_INNER_TYPES(navigation_timing)
#include USE_INNER_TYPES(service_workers)

class navigation_timing::performance_navigation_timing
        : public resource_timing::performance_resource_timing
{
public constructors:
    DOM_CTORS(performance_navigation_timing);
    performance_navigation_timing() = default;

public js_properties:
    ext::property<hr_time::dom_high_res_time_stamp> unload_event_start;
    ext::property<hr_time::dom_high_res_time_stamp> unload_event_end;
    ext::property<hr_time::dom_high_res_time_stamp> dom_interactive;
    ext::property<hr_time::dom_high_res_time_stamp> dom_content_loaded_event_start;
    ext::property<hr_time::dom_high_res_time_stamp> dom_content_loaded_event_end;
    ext::property<hr_time::dom_high_res_time_stamp> dom_complete;
    ext::property<hr_time::dom_high_res_time_stamp> load_event_start;
    ext::property<hr_time::dom_high_res_time_stamp> load_event_end;
    ext::property<hr_time::dom_high_res_time_stamp> type;
    ext::property<ext::number<ushort>> redirect_count;

public cpp_methods:
    auto to_json() const -> ext::string override;

private cpp_properties:
    std::unique_ptr<html::detail::document_load_timing_info_t> m_document_load_timing;
    std::unique_ptr<html::detail::document_unload_timing_info_t> m_previous_document_unload_timing;
    ext::number<ushort> m_redirect_count;
    detail::navigation_timing_type_t m_navigation_type;
    service_workers::detail::service_worker_timing_info_t& m_service_worker_timing;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_NAVIGATION_TIMING_PERFORMANCE_NAVIGATION_TIMING_HPP
