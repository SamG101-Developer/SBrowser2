#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERFORMANCE_TIMELINE_PERFORMANCE_ENTRY_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERFORMANCE_TIMELINE_PERFORMANCE_ENTRY_PRIVATE_HPP

#include "ext/pimpl.ixx"



#include INCLUDE_INNER_TYPES(hr_time)


DEFINE_PRIVATE_CLASS(performance_timeline, performance_entry) : virtual dom_object_private
{
    ext::string name;
    ext::string entry_type;
    hr_time::dom_high_res_time_stamp start_time;
    hr_time::dom_high_res_time_stamp duration;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERFORMANCE_TIMELINE_PERFORMANCE_ENTRY_PRIVATE_HPP
