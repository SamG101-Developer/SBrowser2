module;
#include "ext/macros.hpp"


export module apis.longtasks.task_attribution_timing;
import apis.performance_timeline.performance_entry;

import apis.hr_time.types;
import ext.core;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(longtasks, task_attribution_timing) final
        : public performance_timeline::performance_entry
{
public constructors:
    MAKE_PIMPL(task_attribution_timing);
    MAKE_V8_AVAILABLE(WINDOW);

private js_properties:
    DEFINE_GETTER(container_type, ext::string);
    DEFINE_GETTER(container_src, ext::string);
    DEFINE_GETTER(container_id, ext::string);
    DEFINE_GETTER(container_name, ext::string);

    DEFINE_GETTER(name, ext::string_view) override;
    DEFINE_GETTER(entry_type, ext::string_view) override;
    DEFINE_GETTER(start_time, hr_time::dom_high_res_time_stamp) override;
    DEFINE_GETTER(duration, hr_time::dom_high_res_time_stamp) override;
};
