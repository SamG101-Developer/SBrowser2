#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_ELEMENTS_SVG_GRAPHICS_ELEMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_ELEMENTS_SVG_GRAPHICS_ELEMENT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "svg/elements/svg_element_private.hpp"
#include "svg/mixins/svg_tests_private.hpp"

namespace svg::types {class svg_animated_transform_list;}


DEFINE_PRIVATE_CLASS(svg::elements, svg_graphics_element)
        : svg::elements::svg_element_private
        , svg::mixins::svg_tests_private
{
    std::unique_ptr<types::svg_animated_transform_list> transform;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_ELEMENTS_SVG_GRAPHICS_ELEMENT_PRIVATE_HPP
