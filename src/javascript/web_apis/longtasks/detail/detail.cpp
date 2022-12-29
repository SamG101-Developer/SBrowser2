module;
#include "ext/macros/language_shorthand.hpp"
#include <range/v3/view/transform.hpp>
#include <range/v3/view/concat.hpp>
#include <range/v3/view/join.hpp>

module apis.longtasks.detail;

import apis.hr_time.types;
import apis.html.detail;
import apis.html.types;

import ext.core;
import js.env.realms;


auto longtasks::detail::report_long_tasks(
        hr_time::dom_high_res_time_stamp start_time,
        hr_time::dom_high_res_time_stamp end_time,
        ext::span<html::detail::browsing_context_t*> browsing_contexts,
        html::detail::task_t&& task) -> void
{
    return_if (end_time - start_time <= 50);

    // Get the 'browsing_contexts's descendant browsing contexts in a list (list of list of contexts), and append the
    // list of original (topmost) 'browsing_contexts'. Flatten the list of lists into a list of contexts. Transform
    // this large list of browsing contexts into their active document's relevant environments, and convert to a set.
    auto destination_realms = browsing_contexts
            | ranges::views::transform(std::mem_fn(html::detail::browsing_context_t::descendant_browsing_contexts))
            | ranges::views::concat(browsing_contexts)
            | ranges::views::join
            | ranges::views::transform(std::mem_fn(html::detail::browsing_context_t::active_document))
            | ranges::views::transform(&js::env::env::relevant)
            | ranges::to_set;
}
