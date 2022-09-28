#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_NAVIGATION_TIMING_PERFORMANCE_NAVIGATION_TIMING_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_NAVIGATION_TIMING_PERFORMANCE_NAVIGATION_TIMING_HPP

#include "resource_timing/performance_resource_timing.hpp"
namespace navigation_timing {class performance_navigation_timing;}

#include <memory>
#include INCLUDE_INNER_TYPES(hr_time)
#include INCLUDE_INNER_TYPES(navigation_timing)


#include "performance_navigation_timing_private.hpp"

class navigation_timing::performance_navigation_timing
        : public resource_timing::performance_resource_timing
{
public constructors:
    DOM_CTORS(performance_navigation_timing);
    MAKE_PIMPL(performance_navigation_timing);
    MAKE_V8_AVAILABLE;
    MAKE_STRINGIFIER;

private js_properties:
    DEFINE_GETTER(unload_event_start, hr_time::dom_high_res_time_stamp);
    DEFINE_GETTER(unload_event_end, hr_time::dom_high_res_time_stamp);
    DEFINE_GETTER(dom_interactive, hr_time::dom_high_res_time_stamp);
    DEFINE_GETTER(dom_content_loaded_event_start, hr_time::dom_high_res_time_stamp);
    DEFINE_GETTER(dom_content_loaded_event_end, hr_time::dom_high_res_time_stamp);
    DEFINE_GETTER(dom_complete, hr_time::dom_high_res_time_stamp);
    DEFINE_GETTER(load_event_start, hr_time::dom_high_res_time_stamp);
    DEFINE_GETTER(load_event_end, hr_time::dom_high_res_time_stamp);
    DEFINE_GETTER(type, detail::navigation_timing_type_t);
    DEFINE_GETTER(redirect_count, ext::number<ushort>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_NAVIGATION_TIMING_PERFORMANCE_NAVIGATION_TIMING_HPP
