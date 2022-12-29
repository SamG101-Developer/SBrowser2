module;
#include "ext/macros/macros.hpp"


export module apis.largest_contentful_paint.detail;
import apis.css.geometry.types;
import apis.dom.types;
import apis.fetch.types;
import apis.hr_time.types;
import ext.core;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(largest_contentful_paint)
{
    auto potentially_add_largest_contentful_paint_entry(
            css::geometry::dom_rect_readonly* intersection_rect, fetch::request* request,
            hr_time::dom_high_res_time_stamp render_time, hr_time::dom_high_res_time_stamp load_time,
            dom::element* element, dom::document* document) -> void;

    auto create_largest_contentful_paint_entry(
            ext::map<ext::string, ext::any>&& construct_map, dom::document* document) -> void;
}
