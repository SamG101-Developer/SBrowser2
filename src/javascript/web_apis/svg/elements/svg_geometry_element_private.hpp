#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_ELEMENTS_SVG_GEOMETRY_ELEMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_ELEMENTS_SVG_GEOMETRY_ELEMENT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "svg/elements/svg_element_private.hpp"

namespace svg::types {class svg_animated_number;}


DEFINE_PRIVATE_CLASS(svg::elements, svg_geometry_element) : svg::elements::svg_element_private
{
    std::unique_ptr<types::svg_animated_number> path_lengths;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_ELEMENTS_SVG_GEOMETRY_ELEMENT_PRIVATE_HPP
