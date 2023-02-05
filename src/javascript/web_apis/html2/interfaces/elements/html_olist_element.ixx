module;
#include "ext/macros.hpp"


export module apis.html.html_olist_element;
import apis.html.html_element;


DEFINE_PUBLIC_CLASS(html, html_olist_element) final
        : public html::html_element
{
public constructors:
    html_olist_element();
    MAKE_PIMPL(html_olist_element);
    MAKE_V8_AVAILABLE();

private js_properties:
    DEFINE_GETTER(reversed, ext::boolean);
    DEFINE_GETTER(start, ext::number<long>);
    DEFINE_GETTER(type, ext::string_view);

    DEFINE_SETTER(reversed, ext::boolean);
    DEFINE_SETTER(start, ext::number<long>);
    DEFINE_SETTER(type, ext::string);
};
