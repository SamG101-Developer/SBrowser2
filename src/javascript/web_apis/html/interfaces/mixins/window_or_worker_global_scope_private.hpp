#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_WINDOW_OR_WORKER_GLOBAL_SCOPE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_WINDOW_OR_WORKER_GLOBAL_SCOPE_PRIVATE_HPP

#include "ext/pimpl.ixx"


#include INCLUDE_INNER_TYPES(hr_time)




DEFINE_PRIVATE_CLASS(html::mixins, window_or_worker_global_scope) : virtual dom_object_private
{
    ext::map<ext::number<long>, hr_time::dom_high_res_time_stamp> active_timers;

    /* [Reporting] */
    ext::vector<std::unique_ptr<reporting::detail::endpoint_t>> endpoints;
    ext::vector<std::unique_ptr<reporting::detail::report_t>> reports;
    ext::vector<std::unique_ptr<reporting::detail::reporting_observer_t>> registered_reporting_observers;
    ext::vector<std::unique_ptr<reporting::detail::report_t>> report_buffer;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_WINDOW_OR_WORKER_GLOBAL_SCOPE_PRIVATE_HPP
