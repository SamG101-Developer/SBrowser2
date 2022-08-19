#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_LONGTASKS_DETAIL_PROCESSING_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_LONGTASKS_DETAIL_PROCESSING_INTERNALS_HPP

#include "ext/number.hpp"
#include <v8-platform.h>
#include USE_INNER_TYPES(html)
#include USE_INNER_TYPES(high_resolution_time)

namespace longtasks::detail
{
    auto report_long_tasks(
            const ext::number<double>& start_time,
            const ext::number<double>& end_time,
            html::detail::browsing_context_t* browsing_context,
            v8::Task& task)
            -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_LONGTASKS_DETAIL_PROCESSING_INTERNALS_HPP
