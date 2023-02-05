module;
#include "ext/macros.hpp"


export module apis.html.html_link_element;
import apis.html.html_element;


DEFINE_PUBLIC_CLASS(html, html_link_element) final
        : public html::html_element
        , public cssom::mixins::link_style
{
public constructors:
    html_link_element();
    MAKE_PIMPL(html_link_element);
    MAKE_V8_AVAILABLE();

private js_properties:
    DEFINE_GETTER(href, ext::string_view);
    DEFINE_GETTER(cross_origin, ext::optional<ext::string_view>);
    DEFINE_GETTER(rel, ext::string_view);
    DEFINE_GETTER(as, ext::string_view);
    DEFINE_GETTER(rel_list, ext::span<ext::string>);
    DEFINE_GETTER(media, ext::string_view);
    DEFINE_GETTER(integrity, ext::string_view);
    DEFINE_GETTER(hreflang, ext::string_view);
    DEFINE_GETTER(type, ext::string_view);
    DEFINE_GETTER(sizes, ext::span<ext::string>);
    DEFINE_GETTER(image_srcset, ext::string);
    DEFINE_GETTER(image_sizes, ext::string);
    DEFINE_GETTER(referrer_policy, referrer_policy::detail::referrer_policy_t)
    DEFINE_GETTER(blocking, ext::span<ext::string>);
    DEFINE_GETTER(disabled, ext::boolean);

    DEFINE_SETTER(href, ext::string);
    DEFINE_SETTER(cross_origin, ext::optional<ext::string>);
    DEFINE_SETTER(rel, ext::string);
    DEFINE_SETTER(as, ext::string);
    DEFINE_SETTER(media, ext::string);
    DEFINE_SETTER(integrity, ext::string);
    DEFINE_SETTER(hreflang, ext::string);
    DEFINE_SETTER(type, ext::string);
    DEFINE_SETTER(image_srcset, ext::string);
    DEFINE_SETTER(image_sizes, ext::string);
    DEFINE_SETTER(referrer_policy, referrer_policy::detail::referrer_policy_t)
    DEFINE_SETTER(disabled, ext::boolean);
};
