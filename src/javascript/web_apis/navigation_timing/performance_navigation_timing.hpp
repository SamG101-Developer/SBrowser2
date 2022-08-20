#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_NAVIGATION_TIMING_PERFORMANCE_NAVIGATION_TIMING_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_NAVIGATION_TIMING_PERFORMANCE_NAVIGATION_TIMING_HPP

#include "resource_timing/performance_resource_timing.hpp"
namespace navigation_timing {class performance_navigation_timing;}

#include <memory>
#include USE_INNER_TYPES(high_resolution_time)
#include USE_INNER_TYPES(html)
#include USE_INNER_TYPES(navigation_timing)

class navigation_timing::performance_navigation_timing
        : public resource_timing::performance_resource_timing
{
public constructors:
    DOM_CTORS(performance_navigation_timing);
    performance_navigation_timing() = default;

public js_properties:
    ext::property<high_resolution_time::detail::dom_high_res_time_stamp_t> unload_event_start;
    ext::property<high_resolution_time::detail::dom_high_res_time_stamp_t> unload_event_end;
    ext::property<high_resolution_time::detail::dom_high_res_time_stamp_t> dom_interactive;
    ext::property<high_resolution_time::detail::dom_high_res_time_stamp_t> dom_content_loaded_event_start;
    ext::property<high_resolution_time::detail::dom_high_res_time_stamp_t> dom_content_loaded_event_end;
    ext::property<high_resolution_time::detail::dom_high_res_time_stamp_t> dom_complete;
    ext::property<high_resolution_time::detail::dom_high_res_time_stamp_t> load_event_start;
    ext::property<high_resolution_time::detail::dom_high_res_time_stamp_t> load_event_end;
    ext::property<high_resolution_time::detail::dom_high_res_time_stamp_t> type;
    ext::property<ext::number<ushort>> redirect_count;

public cpp_methods:
    auto to_json() const -> ext::string override;

private cpp_properties:
    std::unique_ptr<html::detail::document_load_timing_info_t> m_document_load_timing;
    std::unique_ptr<html::detail::document_unload_timing_info_t> m_previous_document_unload_timing;
    ext::number<ushort> m_redirect_count;
    detail::navigation_timing_type_t m_navigation_type;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_NAVIGATION_TIMING_PERFORMANCE_NAVIGATION_TIMING_HPP
