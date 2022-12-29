#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_NAVIGATORS_MIXINS_NAVIGATOR_ON_LINE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_NAVIGATORS_MIXINS_NAVIGATOR_ON_LINE_HPP

// Inheritance Includes & This Class

namespace html::navigators::mixins {class navigator_on_line;}
namespace html::navigators::mixins {class navigator_on_line_private;}

// Other Includes & Forward Declarations


class html::navigators::mixins::navigator_on_line
        : virtual public dom_object
{
public constructors:
    navigator_on_line();
    MAKE_PIMPL(navigator_on_line);
    MAKE_V8_AVAILABLE;

public js_properties:
    DEFINE_GETTER(on_line, ext::boolean);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_NAVIGATORS_MIXINS_NAVIGATOR_ON_LINE_HPP
