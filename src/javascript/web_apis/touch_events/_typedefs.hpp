#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_TOUCH_EVENTS__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_TOUCH_EVENTS__TYPEDEFS_HPP



#include "ext/string.hpp"

namespace touch_events::detail
{
    enum class touch_type_t {DIRECT, STYLUS};

    using touch_init_t = ext::map<ext::string, ext::any>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_TOUCH_EVENTS__TYPEDEFS_HPP
