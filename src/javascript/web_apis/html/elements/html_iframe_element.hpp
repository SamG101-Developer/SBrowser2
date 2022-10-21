#pragma once
#ifndef SBROWSER2_HTML_IFRAME_ELEMENT_HPP
#define SBROWSER2_HTML_IFRAME_ELEMENT_HPP

#include "html/elements/html_element.hpp"
#include "html/mixins/lazy_loadable.hpp"
namespace html::elements {class html_iframe_element;}
namespace html::elements {class html_iframe_element_private;}

#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(referrer_policy)
namespace dom::nodes {class document;}
namespace dom::nodes {class window_proxy;}
namespace permissions_policy {class permissions_policy_object;}


class html::elements::html_iframe_element
        : public html_element
        , public mixins::lazy_loadable
{
public constructors:
    DOM_CTORS(html_iframe_element);
    MAKE_PIMPL(html_iframe_element);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto get_svg_document() -> dom::nodes::document*;

private js_properties:
    /* [HTML] */
    DEFINE_GETTER(src, ext::string_view);
    DEFINE_GETTER(srcdoc, ext::string_view);
    DEFINE_GETTER(name, ext::string_view);
    DEFINE_GETTER(sandbox, ext::string_view);
    DEFINE_GETTER(allow, ext::string_view);
    DEFINE_GETTER(allow_fullscreen, ext::boolean);
    DEFINE_GETTER(width, ext::string_view);
    DEFINE_GETTER(height, ext::string_view);
    DEFINE_GETTER(referrer_policy, referrer_policy::detail::referrer_policy_t);
    DEFINE_GETTER(loading, detail::lazy_loading_t);
    DEFINE_GETTER(content_document, dom::nodes::document*);
    DEFINE_GETTER(content_window, dom::nodes::window_proxy*);

    DEFINE_SETTER(src, ext::string);
    DEFINE_SETTER(srcdoc, ext::string);
    DEFINE_SETTER(name, ext::string);
    DEFINE_SETTER(allow, ext::string);
    DEFINE_SETTER(allow_fullscreen, ext::boolean);
    DEFINE_SETTER(width, ext::string);
    DEFINE_SETTER(height, ext::string);
    DEFINE_SETTER(referrer_policy, referrer_policy::detail::referrer_policy_t);
    DEFINE_SETTER(loading, detail::lazy_loading_t);

    /* [PERMISSIONS-POLICY] */
    DEFINE_GETTER(permissions_policy, permissions_policy::permissions_policy_object*);
};


#endif //SBROWSER2_HTML_IFRAME_ELEMENT_HPP
