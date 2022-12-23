module;
#include "ext/macros/pimpl.hpp"


export module apis.performance_timeline.performance_entry_private;
import apis.dom_object_private;
import apis.hr_time.types;

import ext.core;


DEFINE_PRIVATE_CLASS(performance_timeline, performance_entry)
        : virtual dom_object_private
{
    ext::string name;
    ext::string entry_type;
    hr_time::dom_high_res_time_stamp start_time;
    hr_time::dom_high_res_time_stamp duration;
};
