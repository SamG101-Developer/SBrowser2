#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAINT_TIMING_DETAIL_PROCESSING_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAINT_TIMING_DETAIL_PROCESSING_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/string.hpp"
#include USE_INNER_TYPES(high_resolution_time)
namespace dom::nodes {class document;}


namespace paint_timing::detail
{
    auto should_report_first_contentful_paint(
            dom::nodes::document* document)
            -> ext::boolean;

    auto mark_paint_timing(
            dom::nodes::document* document)
            -> void;

    auto report_paint_timing(
            dom::nodes::document* document,
            ext::string&& paint_type,
            high_resolution_time::detail::dom_high_res_time_stamp_t)
            -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAINT_TIMING_DETAIL_PROCESSING_INTERNALS_HPP
