#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_NAVIGATORS_MIME_TYPE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_NAVIGATORS_MIME_TYPE_HPP

// Inheritance Includes & This Class
#include "dom_object.hpp"
namespace html::navigators {class mime_type;}
namespace html::navigators {class mime_type_private;}

// Other Includes & Forward Declarations
namespace html::navigators {class plugin;}


class html::navigators::mime_type
        : virtual public dom_object
{
public constructors:
    mime_type();
    MAKE_PIMPL(mime_type);
    MAKE_V8_AVAILABLE;

public js_properties:
    DEFINE_GETTER(type, ext::string_view);
    DEFINE_GETTER(description, ext::string_view);
    DEFINE_GETTER(suffixes, ext::string_view);
    DEFINE_GETTER(enabled_plugin, plugin*);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_NAVIGATORS_MIME_TYPE_HPP
