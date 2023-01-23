module;
#include "ext/macros.hpp"


export module apis.navigation_timing.performance_navigation_timing;
import apis.resource_timing.performance_resource_timing;

import apis.hr_time.types;
import apis.navigation_timing.types;


DEFINE_PUBLIC_CLASS(navigation_timing, performance_navigation_timing) final
        : public resource_timing::performance_resource_timing
{
public constructors:
    DOM_CTORS(performance_navigation_timing);
    MAKE_PIMPL(performance_navigation_timing);
    MAKE_V8_AVAILABLE(WINDOW);
    MAKE_STRINGIFIER;

private js_properties:
    DEFINE_GETTER(name, ext::string_view) override;
    DEFINE_GETTER(entry_type, ext::string_view) override;
    DEFINE_GETTER(start_time, hr_time::dom_high_res_time_stamp) override;
    DEFINE_GETTER(duration, hr_time::dom_high_res_time_stamp) override;

    DEFINE_GETTER(worker_start, hr_time::dom_high_res_time_stamp) override;
    DEFINE_GETTER(redirect_start, hr_time::dom_high_res_time_stamp) override;
    DEFINE_GETTER(redirect_end, hr_time::dom_high_res_time_stamp) override;
    DEFINE_GETTER(fetch_start, hr_time::dom_high_res_time_stamp) override;

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
