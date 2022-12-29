#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_META_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_META_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_meta_element;}
namespace html::elements {class html_meta_element_private;}

#include INCLUDE_INNER_TYPES(html)


class html::elements::html_meta_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_meta_element);
    MAKE_PIMPL(html_meta_element);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(name, ext::string_view);
    DEFINE_GETTER(content, ext::string_view);
    DEFINE_GETTER(media, ext::string_view);
    DEFINE_GETTER(http_equiv, detail::http_equiv_t);

    DEFINE_SETTER(name, ext::string);
    DEFINE_SETTER(content, ext::string);
    DEFINE_SETTER(media, ext::string);
    DEFINE_SETTER(http_equiv, detail::http_equiv_t);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_META_ELEMENT_HPP
