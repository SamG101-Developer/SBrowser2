#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_LARGEST_CONTENTFUL_PAINT_DETAIL_PROCESSING_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_LARGEST_CONTENTFUL_PAINT_DETAIL_PROCESSING_INTERNALS_HPP

#include "ext/any.hpp"
#include "ext/map.ixx"
#include INCLUDE_INNER_TYPES(hr_time)
namespace dom::nodes {class document; class element;}
namespace fetch {class request;}
namespace css::geometry {class dom_rect_readonly;}

namespace largest_contentful_paint::detail
{
    auto potentially_add_largest_contentful_paint_entry(
            css::geometry::dom_rect_readonly* intersection_rect,
            fetch::request* request,
            hr_time::dom_high_res_time_stamp render_time,
            hr_time::dom_high_res_time_stamp load_time,
            dom::nodes::element* element,
            dom::nodes::document* document)
            -> void;

    auto create_largest_contentful_paint_entry(
            ext::map<ext::string, ext::any>&& construct_map,
            dom::nodes::document* document)
            -> void;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_LARGEST_CONTENTFUL_PAINT_DETAIL_PROCESSING_INTERNALS_HPP
