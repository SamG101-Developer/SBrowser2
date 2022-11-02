#ifndef SBROWSER2_HTML_SCRIPT_ELEMENT_HPP
#define SBROWSER2_HTML_SCRIPT_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_script_element;}
namespace html::elements {class html_script_element_private;}

#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(referrer_policy)
#include "ext/variant.hpp"


class html::elements::html_script_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_script_element);
    MAKE_PIMPL(html_script_element);
    MAKE_V8_AVAILABLE;

public js_methods:
    static auto supports(ext::string_view type) -> ext::boolean;

private js_properties:
    DEFINE_GETTER(src, ext::string);
    DEFINE_GETTER(type, ext::string);
    DEFINE_GETTER(no_module, ext::boolean);
    DEFINE_GETTER(async, ext::boolean);
    DEFINE_GETTER(defer, ext::boolean);
    DEFINE_GETTER(cross_origin, html::detail::cross_origin_settings_attribute_t);
    DEFINE_GETTER(text, ext::string);
    DEFINE_GETTER(integrity, ext::string);
    DEFINE_GETTER(referrer_policy, referrer_policy::detail::referrer_policy_t);
    DEFINE_GETTER(blocking, ext::string);

    DEFINE_SETTER(src, ext::string);
    DEFINE_SETTER(type, ext::string);
    DEFINE_SETTER(no_module, ext::boolean);
    DEFINE_SETTER(async, ext::boolean);
    DEFINE_SETTER(defer, ext::boolean);
    DEFINE_SETTER(cross_origin, html::detail::cross_origin_settings_attribute_t);
    DEFINE_SETTER(text, ext::string);
    DEFINE_SETTER(integrity, ext::string);
    DEFINE_SETTER(referrer_policy, referrer_policy::detail::referrer_policy_t);
};


#endif //SBROWSER2_HTML_SCRIPT_ELEMENT_HPP
