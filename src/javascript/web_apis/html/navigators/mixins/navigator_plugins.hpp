#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_NAVIGATORS_MIXINS_NAVIGATOR_PLUGINS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_NAVIGATORS_MIXINS_NAVIGATOR_PLUGINS_HPP

// Inheritance Includes & This Class
#include "dom_object.hpp"
namespace html::navigators::mixins {class navigator_plugins;}
namespace html::navigators::mixins {class navigator_plugins_private;}

// Other Includes & Forward Declarations

namespace html::navigators {class plugin;}
namespace html::navigators {class mime_type;}


class html::navigators::mixins::navigator_plugins
        : virtual public dom_object
{
public constructors:
    navigator_plugins();
    MAKE_PIMPL(navigator_plugins);
    MAKE_V8_AVAILABLE;

public js_properties:
    DEFINE_GETTER(pdf_viewer_enabled, ext::boolean);
    DEFINE_GETTER(plugins, ranges::any_helpful_view<plugin*>);
    DEFINE_GETTER(mime_types, ranges::any_helpful_view<mime_type*>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_NAVIGATORS_MIXINS_NAVIGATOR_PLUGINS_HPP
