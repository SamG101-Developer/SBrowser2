#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_WORKERS_WORKER_GLOBAL_SCOPE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_WORKERS_WORKER_GLOBAL_SCOPE_HPP

#include "dom_object.hpp"
namespace html::workers {class worker_global_scope;}


class html::workers::worker_global_scope
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(worker_global_scope);
    worker_global_scope() = default;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_WORKERS_WORKER_GLOBAL_SCOPE_HPP
