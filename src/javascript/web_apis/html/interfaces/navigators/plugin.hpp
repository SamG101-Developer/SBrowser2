#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_NAVIGATORS_PLUGIN_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_NAVIGATORS_PLUGIN_HPP

// Inheritance Includes & This Class

#include "ext/vector_like.ixx"
namespace html::navigators {class plugin;}
namespace html::navigators {class plugin_private;}

// Other Includes & Forward Declarations
namespace html::navigators {class mime_type;}


class html::navigators::plugin
        : virtual public dom_object
        , public ext::vector_like<mime_type*>
{
public constructors:
    plugin();
    MAKE_PIMPL(plugin);
    MAKE_V8_AVAILABLE;

    auto operator[](ext::number<size_t> index) -> mime_type*& override;
    auto operator[](ext::number<size_t> index) const -> mime_type*& override;
    auto operator[](ext::string_view index) -> mime_type*& override;
    auto operator[](ext::string_view index) const -> mime_type*& override;

public js_properties:
    DEFINE_GETTER(name, ext::string_view);
    DEFINE_GETTER(filename, ext::string_view);
    DEFINE_GETTER(description, ext::string_view);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_NAVIGATORS_PLUGIN_HPP
