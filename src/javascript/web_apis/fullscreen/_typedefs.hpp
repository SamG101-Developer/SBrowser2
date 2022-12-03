#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FULLSCREEN__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FULLSCREEN__TYPEDEFS_HPP


#include "ext/map.ixx"
#include "ext/string.hpp"

namespace fullscreen::detail
{
    enum class fullscreen_navigation_ui_t {AUTO, SHOW, HIDE};

    using fullscreen_options_t = ext::map<ext::string, ext::any>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FULLSCREEN__TYPEDEFS_HPP
