#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAINT_TIMING_DETAIL_PAINT_TIMING_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAINT_TIMING_DETAIL_PAINT_TIMING_INTERNALS_HPP


#include INCLUDE_INNER_TYPES(html)
namespace css::geometry {class dom_rect;}
namespace dom::nodes {class element;}

namespace paint_timing::detail
{
    auto is_paintable_pseudo_element(
            css::css_pseudo::pseudo_element* element)
            -> ext::boolean;

    auto is_contentful_image(
            css::css_images::detail::css_image_t)
            -> ext::boolean;

    auto is_contentful_element(
            dom::nodes::element* element)
            -> ext::boolean;

    auto paintable_boundable_rect(
            dom::nodes::element* element)
            -> css::geometry::dom_rect;

    auto is_paintable_element(
            dom::nodes::element* element)
            -> ext::boolean;

    auto is_paint_timing_eligible(
            const html::detail::browsing_context_t&)
            -> ext::boolean;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAINT_TIMING_DETAIL_PAINT_TIMING_INTERNALS_HPP
