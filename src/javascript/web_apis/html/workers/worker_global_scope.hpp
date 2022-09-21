#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_WORKERS_WORKER_GLOBAL_SCOPE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_WORKERS_WORKER_GLOBAL_SCOPE_HPP

#include "dom_object.hpp"
namespace html::workers {class worker_global_scope;}

#include "ext/vector.hpp"
#include INCLUDE_INNER_TYPES(reporting)
namespace reporting {class registered_observer;}


class html::workers::worker_global_scope
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(worker_global_scope);
    worker_global_scope() = default;

private cpp_properties:
    ext::vector<reporting::detail::endpoint_t*> m_endpoints_list;
    ext::vector<reporting::detail::report_t*> m_reports_list;
    ext::vector<reporting::detail::report_t*> m_reports_buffer;
    ext::vector<reporting::registered_observer*> m_registered_reporting_observer_list;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_WORKERS_WORKER_GLOBAL_SCOPE_HPP
