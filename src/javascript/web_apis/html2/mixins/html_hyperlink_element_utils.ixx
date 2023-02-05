module;
#include "ext/macros.hpp"


export module apis.html::mixins.html_hyperlink_element_utils;
import apis.dom_object;


DEFINE_PUBLIC_CLASS(html::mixins, html_hyperlink_element_utils)
        : public dom_object
{
public constructors:
    html_hyperlink_element_utils();
    MAKE_PIMPL(html_hyperlink_element_utils);
    MAKE_V8_AVAILABLE(MIXIN);

private js_properties:
    DEFINE_GETTER(href, ext::string);
    DEFINE_GETTER(origin, ext::string);
    DEFINE_GETTER(protocol, ext::string);
    DEFINE_GETTER(username, ext::string);
    DEFINE_GETTER(password, ext::string);
    DEFINE_GETTER(host, ext::string);
    DEFINE_GETTER(hostname, ext::string);
    DEFINE_GETTER(port, ext::string);
    DEFINE_GETTER(pathname, ext::string);
    DEFINE_GETTER(search, ext::string);
    DEFINE_GETTER(hash, ext::string);

    DEFINE_SETTER(href, ext::string);
    DEFINE_SETTER(protocol, ext::string);
    DEFINE_SETTER(username, ext::string);
    DEFINE_SETTER(password, ext::string);
    DEFINE_SETTER(host, ext::string);
    DEFINE_SETTER(hostname, ext::string);
    DEFINE_SETTER(port, ext::string);
    DEFINE_SETTER(pathname, ext::string);
    DEFINE_SETTER(search, ext::string);
    DEFINE_SETTER(hash, ext::string);
};
