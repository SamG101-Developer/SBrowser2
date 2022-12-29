module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/macros.hpp"
#include "ext/macros/other.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.longtasks.performance_long_task_timing;
import apis.performance_timeline.performance_entry;

import apis.hr_time.types;
import apis.longtasks.types;
import ext.core;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(longtasks, performance_long_task_timing) final
        : public performance_timeline::performance_entry
{
public constructors:
    MAKE_PIMPL(performance_long_task_timing);
    MAKE_V8_AVAILABLE(WINDOW);
    MAKE_STRINGIFIER;

private js_properties:
    DEFINE_GETTER(attribution, ext::span<task_attribution_timing*>);

    DEFINE_GETTER(name, ext::string_view) override;
    DEFINE_GETTER(entry_type, ext::string_view) override;
    DEFINE_GETTER(start_time, hr_time::dom_high_res_time_stamp) override;
    DEFINE_GETTER(duration, hr_time::dom_high_res_time_stamp) override;
};
