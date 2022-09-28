#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_LONGTASKS_DETAIL_PROCESSING_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_LONGTASKS_DETAIL_PROCESSING_INTERNALS_HPP

#include "ext/number.hpp"
#include <v8-platform.h>
#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(hr_time)
namespace dom::nodes {class element;}
namespace performance_timeline {class performance_entry;}


namespace longtasks::detail
{
    auto culprit_browsing_context_container(
            const performance_timeline::performance_entry* performance_entry)
            -> dom::nodes::element*;

    auto report_long_tasks(
            hr_time::dom_high_res_time_stamp start_time,
            hr_time::dom_high_res_time_stamp end_time,
            ext::vector_view<html::detail::browsing_context_t*> browsing_contexts,
            html::detail::task_t&& task)
            -> void;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_LONGTASKS_DETAIL_PROCESSING_INTERNALS_HPP
