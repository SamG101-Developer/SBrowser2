#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_MOD_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_MOD_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_mod_element;}
namespace html::elements {class html_mod_element_private;}


class html::elements::html_mod_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_mod_element);
    MAKE_PIMPL(html_mod_element);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(cite, ext::string_view);
    DEFINE_GETTER(date_time, ext::string_view);

    DEFINE_SETTER(cite, ext::string);
    DEFINE_SETTER(date_time, ext::string);
};



#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_MOD_ELEMENT_HPP
