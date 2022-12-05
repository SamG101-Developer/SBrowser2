#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVER_TIMING_PERFORMANCE_SERVER_TIMING_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVER_TIMING_PERFORMANCE_SERVER_TIMING_HPP

// Inheritance Includes & This Class

namespace server_timing {class performance_server_timing;}
namespace server_timing {class performance_server_timing_private;}

// Other Includes & Forward Declarations
#include INCLUDE_INNER_TYPES(hr_time)


class server_timing::performance_server_timing
        : public dom_object
{
public constructors:
    performance_server_timing();
    MAKE_PIMPL(performance_server_timing);
    MAKE_V8_AVAILABLE;
    MAKE_STRINGIFIER;

public js_properties:
    DEFINE_GETTER(name, ext::string_view);
    DEFINE_GETTER(duration, hr_time::dom_high_res_time_stamp);
    DEFINE_GETTER(description, ext::string_view);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVER_TIMING_PERFORMANCE_SERVER_TIMING_HPP
