module;
#include "ext/macros.hpp"


export module apis.html.html_mod_element;
import apis.html.html_element;


DEFINE_PUBLIC_CLASS(html, html_mod_element) final
        : public html::html_element
{
public constructors:
    html_mod_element();
    MAKE_PIMPL(html_mod_element);
    MAKE_V8_AVAILABLE(WINDOW);

private js_properties:
    DEFINE_GETTER(cite, ext::string_view);
    DEFINE_GETTER(date_time, ext::string_view);
    DEFINE_SETTER(cite, ext::string);
    DEFINE_SETTER(date_time, ext::string);
};
