#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_USER_TIMING__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_USER_TIMING__TYPEDEFS_HPP

#include "ext/any.hpp"
#include "ext/map.ixx"
#include "ext/string.hpp"


namespace user_timing::detail
{
    using performance_mark_options_t = ext::map<ext::string, ext::any>;
    using performance_measure_options_t = ext::map<ext::string, ext::any>;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_USER_TIMING__TYPEDEFS_HPP
