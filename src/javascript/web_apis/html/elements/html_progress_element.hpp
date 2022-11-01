#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_PROGRESS_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_PROGRESS_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_progress_element;}
namespace html::elements {class html_progress_element_private;}


class html::elements::html_progress_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_progress_element);
    MAKE_PIMPL(html_progress_element);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(value, ext::number<double>);
    DEFINE_GETTER(max, ext::number<double>);
    DEFINE_GETTER(position, ext::number<double>);
    DEFINE_GETTER(labels, std::unique_ptr<ext::vector<dom::nodes::node*>>);

    DEFINE_SETTER(value, ext::number<double>);
    DEFINE_SETTER(max, ext::number<double>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_PROGRESS_ELEMENT_HPP
