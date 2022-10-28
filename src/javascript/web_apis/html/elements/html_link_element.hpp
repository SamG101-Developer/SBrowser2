#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_LINK_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_LINK_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_link_element;}
namespace html::elements {class html_link_element_private;}

#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(referrer_policy)
#include "ext/span.hpp"


class html::elements::html_link_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_link_element);
    MAKE_PIMPL(html_link_element);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(href, ext::string_view);
    DEFINE_GETTER(cross_origin, ext::string_view);
    DEFINE_GETTER(rel, detail::rel_t);
    DEFINE_GETTER(as, ext::string);
    DEFINE_GETTER(media, ext::string);
    DEFINE_GETTER(integrity, ext::string);
    DEFINE_GETTER(hreflang, ext::string);
    DEFINE_GETTER(type, ext::string);
    DEFINE_GETTER(image_srcset, ext::string);
    DEFINE_GETTER(image_sizes, ext::string);
    DEFINE_GETTER(referrer, referrer_policy::detail::referrer_policy_t);
    DEFINE_GETTER(disabled, ext::boolean);
    DEFINE_GETTER(sizes, ext::vector_span<ext::string>);
    DEFINE_GETTER(blocking, ext::vector_span<ext::string>);

    DEFINE_SETTER(href, ext::string);
    DEFINE_SETTER(cross_origin, ext::string);
    DEFINE_SETTER(rel, detail::rel_t);
    DEFINE_SETTER(as, ext::string);
    DEFINE_SETTER(media, ext::string);
    DEFINE_SETTER(integrity, ext::string);
    DEFINE_SETTER(hreflang, ext::string);
    DEFINE_SETTER(type, ext::string);
    DEFINE_SETTER(image_srcset, ext::string);
    DEFINE_SETTER(image_sizes, ext::string);
    DEFINE_SETTER(referrer, referrer_policy::detail::referrer_policy_t);
    DEFINE_SETTER(disabled, ext::boolean);

};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_LINK_ELEMENT_HPP
