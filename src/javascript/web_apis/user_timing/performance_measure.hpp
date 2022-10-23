#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_USER_TIMING_PERFORMANCE_MEASURE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_USER_TIMING_PERFORMANCE_MEASURE_HPP

// Inheritance Includes & This Class
#include "performance_timeline/performance_entry.hpp"
namespace user_timing {class performance_measure;}
namespace user_timing {class performance_measure_private;}

// Other Includes & Forward Declarations


class user_timing::performance_measure
        : public performance_timeline::performance_entry
{
public constructors:
    performance_measure();
    MAKE_PIMPL(performance_measure);
    MAKE_V8_AVAILABLE;

public js_properties:
    DEFINE_GETTER(detail, ext::any);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_USER_TIMING_PERFORMANCE_MEASURE_HPP
