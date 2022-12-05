#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_TYPES_SVG_NUMBER_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_TYPES_SVG_NUMBER_PRIVATE_HPP

#include "ext/pimpl.ixx"


#include "ext/memory.ixx"

namespace svg::elements {class svg_element;}


DEFINE_PRIVATE_CLASS(svg::types, svg_number) : dom_object_private
{
    ext::number<float> value;
    ext::boolean readonly;
    std::observer_ptr<elements::svg_element> associated_element;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_TYPES_SVG_NUMBER_PRIVATE_HPP
