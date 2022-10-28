#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_METER_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_METER_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_meter_element;}
namespace html::elements {class html_meter_element_private;}


class html::elements::html_meter_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_meter_element);
    MAKE_PIMPL(html_meter_element);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(value, ext::number<double>);
    DEFINE_GETTER(min, ext::number<double>);
    DEFINE_GETTER(max, ext::number<double>);
    DEFINE_GETTER(low, ext::number<double>);
    DEFINE_GETTER(high, ext::number<double>);
    DEFINE_GETTER(optimum, ext::number<double>);
    DEFINE_GETTER(labels, ext::vector_span<dom::nodes::node*>);

    DEFINE_SETTER(value, ext::number<double>);
    DEFINE_SETTER(min, ext::number<double>);
    DEFINE_SETTER(max, ext::number<double>);
    DEFINE_SETTER(low, ext::number<double>);
    DEFINE_SETTER(high, ext::number<double>);
    DEFINE_SETTER(optimum, ext::number<double>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_METER_ELEMENT_HPP
