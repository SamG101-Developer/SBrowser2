#include "processing_internals.hpp"




#include "hr_time/detail/time_internals.hpp"
#include "paint_timing/detail/paint_timing_internals.hpp"

#include <range/v3/view/filter.hpp>


auto paint_timing::detail::should_report_first_contentful_paint(
        dom::nodes::document* document)
        -> ext::boolean
{
    return_if (document->d_func()->previously_reported_paints.contains("first-contentful-paint")) false;
    return !ranges::empty(dom::detail::descendants(document)
            | ranges::views::filter(detail::is_paintable_element)
            | ranges::views::filter(detail::is_contentful_element));
}


auto paint_timing::detail::mark_paint_timing(
        dom::nodes::document* document)
        -> void
{
    auto e = js::env::env::relevant(document);

    return_if (!detail::is_paint_timing_eligible(document->d_func()->browsing_context));
    auto paint_timestamp = hr_time::detail::current_hr_time(e.js.global());

    // TODO
}
