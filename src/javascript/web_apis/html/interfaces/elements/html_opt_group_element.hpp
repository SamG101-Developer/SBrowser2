#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_OPT_GROUP_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_OPT_GROUP_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_opt_group_element;}
namespace html::elements {class html_opt_group_element_private;}


class html::elements::html_opt_group_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_opt_group_element);
    MAKE_PIMPL(html_opt_group_element);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(disabled, ext::boolean);
    DEFINE_GETTER(label, ext::string_view);

    DEFINE_SETTER(disabled, ext::boolean);
    DEFINE_SETTER(label, ext::string);
};



#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_OPT_GROUP_ELEMENT_HPP
