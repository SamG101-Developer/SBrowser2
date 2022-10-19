#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_WORKERS_WORKER_GLOBAL_SCOPE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_WORKERS_WORKER_GLOBAL_SCOPE_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"
#include "html/mixins/window_or_worker_global_scope_private.hpp"


DEFINE_PRIVATE_CLASS(html::workers, worker_global_scope)
        : virtual dom_object_private
        , mixins::window_or_worker_global_scope_private
{};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_WORKERS_WORKER_GLOBAL_SCOPE_PRIVATE_HPP
