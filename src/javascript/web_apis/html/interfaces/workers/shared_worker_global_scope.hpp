#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_WORKERS_SHARED_WORKER_GLOBAL_SCOPE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_WORKERS_SHARED_WORKER_GLOBAL_SCOPE_HPP

// Inheritance Includes & This Class
#include "html/workers/worker_global_scope.hpp"
namespace html::workers {class shared_worker_global_scope;}
namespace html::workers {class shared_worker_global_scope_private;}

// Other Includes & Forward Declarations


class html::workers::shared_worker_global_scope
        : public html::workers::worker_global_scope
{
public constructors:
    shared_worker_global_scope();
    MAKE_PIMPL(shared_worker_global_scope);
    MAKE_V8_AVAILABLE;

private js_methods:
    auto close() -> void;

private js_properties:
    DEFINE_GETTER(name, ext::string_view);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_WORKERS_SHARED_WORKER_GLOBAL_SCOPE_HPP
