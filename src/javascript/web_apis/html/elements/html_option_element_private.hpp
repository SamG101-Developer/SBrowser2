#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_OPTION_ELEMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_OPTION_ELEMENT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "html/elements/html_element_private.hpp"

namespace html::elements {class html_form_element;}


DEFINE_PRIVATE_CLASS(html::elements, html_option_element) : html::elements::html_element_private
{
    ext::boolean disabled;
    ext::string label;
    ext::boolean selected;
    ext::string value;

    auto text() const -> ext::string;
    auto index() const -> ext::number<long>;

    ext::boolean dirtiness;
    ext::boolean selectedness;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_OPTION_ELEMENT_PRIVATE_HPP
