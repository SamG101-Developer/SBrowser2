#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERFORMANCE_TIMELINE_PERFORMANCE_ENTRY_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERFORMANCE_TIMELINE_PERFORMANCE_ENTRY_HPP

#include "dom_object.hpp"
namespace performance_timeline {class performance_entry;}
namespace performance_timeline {class performance_entry_private;}

#include INCLUDE_INNER_TYPES(hr_time)


class performance_timeline::performance_entry
        : public virtual dom_object
{
public constructors:
    performance_entry();
    MAKE_PIMPL(performance_entry);
    MAKE_V8_AVAILABLE;
    MAKE_STRINGIFIER;

protected cpp_accessors:
    virtual DEFINE_GETTER(name, ext::string) = 0;
    virtual DEFINE_GETTER(entry_type, ext::string) = 0;
    virtual DEFINE_GETTER(start_time, hr_time::dom_high_res_time_stamp) = 0;
    virtual DEFINE_GETTER(duration, hr_time::dom_high_res_time_stamp) = 0;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERFORMANCE_TIMELINE_PERFORMANCE_ENTRY_HPP
