#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_NAVIGATORS_MIXINS_NAVIGATOR_CONTENT_UTILS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_NAVIGATORS_MIXINS_NAVIGATOR_CONTENT_UTILS_HPP

// Inheritance Includes & This Class
#include "dom_object.hpp"
namespace html::navigators::mixins {class navigator_content_utils;}
namespace html::navigators::mixins {class navigator_content_utils_private;}

// Other Includes & Forward Declarations


class html::navigators::mixins::navigator_content_utils
        : virtual public dom_object
{
public constructors:
    navigator_content_utils();
    MAKE_PIMPL(navigator_content_utils);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto register_protocol_handler(ext::string_view scheme, ext::string_view url) -> void;
    auto unregister_protocol_handler(ext::string_view scheme, ext::string_view url) -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_NAVIGATORS_MIXINS_NAVIGATOR_CONTENT_UTILS_HPP
