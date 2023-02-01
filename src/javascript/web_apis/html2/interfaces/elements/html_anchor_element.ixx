module;
#include "ext/macros.hpp"


export module apis.html.html_anchor_element;
import apis.html.html_element;


DEFINE_PUBLIC_CLASS(html, html_anchor_element)
        : public html::html_element
        , public html::mixins::html_hyperlink_element_utils
{
public constructors:
    html_anchor_element();
    MAKE_PIMPL(html_anchor_element);
    MAKE_V8_AVAILABLE();

private js_properties:
    DEFINE_GETTER(target, ext::string_view);
    DEFINE_GETTER(download, ext::string_view);
    DEFINE_GETTER(ping, ext::string_view);
    DEFINE_GETTER(rel, ext::string_view);
    DEFINE_GETTER(rel_list, ext::span<ext::string>);
    DEFINE_GETTER(hreflang, ext::string_view);
    DEFINE_GETTER(type, ext::string_view);
    DEFINE_GETTER(text, ext::string);
    DEFINE_GETTER(referrer_policy, referrer_policy::detail::referrer_policy_t);

    DEFINE_SETTER(target, ext::string);
    DEFINE_SETTER(download, ext::string);
    DEFINE_SETTER(ping, ext::string);
    DEFINE_SETTER(rel, ext::string);
    DEFINE_SETTER(hreflang, ext::string);
    DEFINE_SETTER(type, ext::string);
    DEFINE_SETTER(text, ext::string);
    DEFINE_SETTER(referrer_policy, referrer_policy::detail::referrer_policy_t);
};
