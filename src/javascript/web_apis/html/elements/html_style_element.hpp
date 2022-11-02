#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_STYLE_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_STYLE_ELEMENT_HPP

#include "html/elements/html_element.hpp"
#include "css/cssom/mixins/link_style.hpp"
namespace html::elements {class html_style_element;}
namespace html::elements {class html_style_element_private;}


class html::elements::html_style_element
        : public html_element
        , public css::cssom::mixins::link_style
{
public constructors:
    DOM_CTORS(html_style_element);
    MAKE_PIMPL(html_style_element);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(disabled, ext::boolean);
    DEFINE_GETTER(media, ext::string_view);
    DEFINE_GETTER(blocking, ext::vector_span<detail::blocking_t>);

    DEFINE_SETTER(disabled, ext::boolean);
    DEFINE_SETTER(media, ext::string);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_STYLE_ELEMENT_HPP
