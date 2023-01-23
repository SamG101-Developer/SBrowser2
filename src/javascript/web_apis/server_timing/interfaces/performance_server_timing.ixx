module;
#include "ext/macros.hpp"


export module apis.server_timing.performance_server_timing;
import apis.dom_object;


DEFINE_PUBLIC_CLASS(server_timing, performance_server_timing) final
        : public dom_object
{
public constructors:
    performance_server_timing();
    MAKE_PIMPL(performance_server_timing);
    MAKE_V8_AVAILABLE(WINDOW | WORKER);
    MAKE_STRINGIFIER;

public js_properties:
    DEFINE_GETTER(name, ext::string_view);
    DEFINE_GETTER(duration, hr_time::dom_high_res_time_stamp);
    DEFINE_GETTER(description, ext::string_view);
};
