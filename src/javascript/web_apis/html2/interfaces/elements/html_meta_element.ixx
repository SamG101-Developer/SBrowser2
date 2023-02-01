module;
#include "ext/macros.hpp"


export module apis.html.html_meta_element;
import apis.html.html_element;


DEFINE_PUBLIC_CLASS(html, html_meta_element)
        : public html::html_element
{
public constructors:
    html_meta_element();
    MAKE_PIMPL(html_meta_element);
    MAKE_V8_AVAILABLE();

private js_properties:
    DEFINE_GETTER(name, ext::string_view);
    DEFINE_GETTER(http_equiv, ext::string_view);
    DEFINE_GETTER(content, ext::string_view);
    DEFINE_GETTER(media, ext::string_view);

    DEFINE_SETTER(name, ext::string);
    DEFINE_SETTER(http_equiv, ext::string);
    DEFINE_SETTER(content, ext::string);
    DEFINE_SETTER(media, ext::string);
};
