#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_SOURCE_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_SOURCE_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_source_element;}
namespace html::elements {class html_source_element_private;}


class html::elements::html_source_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_source_element);
    MAKE_PIMPL(html_source_element);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(src, ext::string_view);
    DEFINE_GETTER(type, ext::string_view);
    DEFINE_GETTER(srcset, ext::string_view);
    DEFINE_GETTER(sizes, ext::string_view);
    DEFINE_GETTER(media, ext::string_view);
    DEFINE_GETTER(width, ext::number<ulong>);
    DEFINE_GETTER(height, ext::number<ulong>);

    DEFINE_SETTER(src, ext::string);
    DEFINE_SETTER(type, ext::string);
    DEFINE_SETTER(srcset, ext::string);
    DEFINE_SETTER(sizes, ext::string);
    DEFINE_SETTER(media, ext::string);
    DEFINE_SETTER(width, ext::number<ulong>);
    DEFINE_SETTER(height, ext::number<ulong>);
};



#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_SOURCE_ELEMENT_HPP
