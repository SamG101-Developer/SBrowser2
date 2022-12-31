module;
#include "ext/macros.hpp"


export module apis.event_timing.performance_event_timing;
import apis.performance_timeline.performance_entry;

import apis.dom.types;
import apis.hr_time.types;
import ext.core;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(event_timing, performance_event_timing) final
        : public performance_timeline::performance_entry
{
public constructors:
    performance_event_timing();
    MAKE_PIMPL(performance_event_timing);
    MAKE_V8_AVAILABLE(WINDOW);
    MAKE_STRINGIFIER;

private js_properties:
    DEFINE_GETTER(processing_start, hr_time::dom_high_res_time_stamp);
    DEFINE_GETTER(processing_end, hr_time::dom_high_res_time_stamp);
    DEFINE_GETTER(cancelable, ext::boolean);
    DEFINE_GETTER(target, dom::node*);
    DEFINE_GETTER(interaction_id, ext::number<ulonglong>);

    DEFINE_GETTER(name, ext::string_view) override;
    DEFINE_GETTER(entry_type, ext::string_view) override;
    DEFINE_GETTER(start_time, hr_time::dom_high_res_time_stamp) override;
    DEFINE_GETTER(duration, hr_time::dom_high_res_time_stamp) override;
};
