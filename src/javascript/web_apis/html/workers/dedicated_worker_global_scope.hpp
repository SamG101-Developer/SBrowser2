#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_WORKERS_DEDICATED_WORKER_GLOBAL_SCOPE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_WORKERS_DEDICATED_WORKER_GLOBAL_SCOPE_HPP

#include "html/workers/worker_global_scope.hpp"
namespace html::workers {class dedicated_worker_global_scope;}

#include INCLUDE_INNER_TYPES(html)


class html::workers::dedicated_worker_global_scope
        : public worker_global_scope
{
public constructors:
    dedicated_worker_global_scope() = default;

public js_methods:
    auto post_message(ext::any&& message, ext::vector_view<void*> transfer) -> void;
    auto post_message(ext::any&& message, detail::structured_serialize_options_t options = {}) -> void;
    auto close() -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_WORKERS_DEDICATED_WORKER_GLOBAL_SCOPE_HPP
