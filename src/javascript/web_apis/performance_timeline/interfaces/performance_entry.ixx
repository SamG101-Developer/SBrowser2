module;
#include "ext/macros.hpp"


export module apis.performance_timeline.performance_entry;
import apis.dom_object;

IMPORT_ALL_TYPES(hr_time);


DEFINE_PUBLIC_CLASS(performance_timeline, performance_entry)
        : public virtual dom_object
{
public constructors:
    performance_entry();
    MAKE_PIMPL(performance_entry);
    MAKE_V8_AVAILABLE(WINDOW);
    MAKE_STRINGIFIER;

protected js_properties:
    virtual DEFINE_GETTER(name, ext::string_view) = 0;
    virtual DEFINE_GETTER(entry_type, ext::string_view) = 0;
    virtual DEFINE_GETTER(start_time, hr_time::dom_high_res_time_stamp) = 0;
    virtual DEFINE_GETTER(duration, hr_time::dom_high_res_time_stamp) = 0;
};
