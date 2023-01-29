module;
#include "ext/macros.hpp"


export module apis.paint_timing.detail;
import apis.dom.types;
import apis.hr_time.types;
import apis.html.types;
import ext.core;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(paint_timing)
{
    // [4.1] - Reporting Paint Timing
    /* [4.1.1] */ auto should_report_first_contentful_paint(dom::document* document) -> ext::boolean;
    /* [4.1.2] */ auto mark_paint_timing(dom::document* document) -> void;
    /* [4.1.3] */ auto report_paint_timing(dom::document* document, ext::string&& paint_type, hr_time::dom_high_res_time_stamp) -> void;

    // [2]
    auto is_paintable_pseudo_element(css::css_pseudo::pseudo_element* element) -> ext::boolean;
    auto is_contentful_image(css::css_images::detail::css_image_t) -> ext::boolean;
    auto is_contentful_element(dom::element* element) -> ext::boolean;
    auto paintable_boundable_rect(dom::element* element) -> css::geometry::dom_rect;
    auto is_paintable_element(dom::element* element) -> ext::boolean;
    auto is_paint_timing_eligible(const html::detail::browsing_context_t& context) -> ext::boolean;
};
