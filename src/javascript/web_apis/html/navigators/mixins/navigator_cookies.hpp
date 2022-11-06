#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_NAVIGATORS_MIXINS_NAVIGATOR_COOKIES_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_NAVIGATORS_MIXINS_NAVIGATOR_COOKIES_HPP

// Inheritance Includes & This Class
#include "dom_object.hpp"
namespace html::navigators::mixins {class navigator_cookies;}
namespace html::navigators::mixins {class navigator_cookies_private;}

// Other Includes & Forward Declarations


class html::navigators::mixins::navigator_cookies
        : virtual public dom_object
{
public constructors:
    navigator_cookies();
    MAKE_PIMPL(navigator_cookies);
    MAKE_V8_AVAILABLE;

public js_properties:
    DEFINE_GETTER(cookie_enabled, ext::boolean);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_NAVIGATORS_MIXINS_NAVIGATOR_COOKIES_HPP
