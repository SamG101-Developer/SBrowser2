#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_METER_ELEMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_METER_ELEMENT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "html/elements/html_element_private.hpp"


DEFINE_PRIVATE_CLASS(html::elements, html_meter_element) : html::elements::html_element_private
{
    ext::number<double> minimum_value;
    ext::number<double> maximum_value;
    ext::number<double> actual_value;

    ext::number<double> low_boundary;
    ext::number<double> high_boundary;
    ext::number<double> optimum_point;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_METER_ELEMENT_PRIVATE_HPP
