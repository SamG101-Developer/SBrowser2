module;
#include "ext/macros.hpp"


export module apis.performance_timeline.performance_entry:p;
import apis.dom_object;

IMPORT_ALL_TYPES(hr_time);


DEFINE_PRIVATE_CLASS(performance_timeline, performance_entry)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(performance_entry);

public:
    ext::string name;
    ext::string entry_type;
    hr_time::dom_high_res_time_stamp start_time;
    hr_time::dom_high_res_time_stamp duration;
};
