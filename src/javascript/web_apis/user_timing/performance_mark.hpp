#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_USER_TIMING_PERFORMANCE_MARK_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_USER_TIMING_PERFORMANCE_MARK_HPP

// Inheritance Includes & This Class
#include "performance_timeline/performance_entry.hpp"
namespace user_timing {class performance_mark;}
namespace user_timing {class performance_mark_private;}

// Other Includes & Forward Declarations
#include INCLUDE_INNER_TYPES(user_timing)


class user_timing::performance_mark
        : public performance_timeline::performance_entry
{
public constructors:
    performance_mark(ext::string&& mark_name, detail::performance_mark_options&& mark_options = {});
    MAKE_PIMPL(performance_mark);
    MAKE_V8_AVAILABLE;

public js_properties:
    DEFINE_GETTER(detail, ext::any);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_USER_TIMING_PERFORMANCE_MARK_HPP
