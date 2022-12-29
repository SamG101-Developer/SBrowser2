module;
#include "ext/macros/pimpl.hpp"


export module apis.longtasks.detail;

import apis.hr_time.types;
import apis.html.types;
import ext.core;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(longtasks)
{
    /* [4.1] */ auto report_long_tasks(hr_time::dom_high_res_time_stamp start_time, hr_time::dom_high_res_time_stamp end_time, ext::span<html::detail::browsing_context_t*> browsing_contexts, html::detail::task_t&& task) -> void;
}
