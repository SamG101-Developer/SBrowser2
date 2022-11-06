#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_WORKERS_DEDICATED_WORKER_GLOBAL_SCOPE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_WORKERS_DEDICATED_WORKER_GLOBAL_SCOPE_HPP

#include "html/workers/worker_global_scope.hpp"
namespace html::workers {class dedicated_worker_global_scope;}
namespace html::workers {class dedicated_worker_global_scope_private;}

#include INCLUDE_INNER_TYPES(html)
#include "ext/span.hpp"


class html::workers::dedicated_worker_global_scope
        : public worker_global_scope
{
public constructors:
    DOM_CTORS(dedicated_worker_global_scope);
    MAKE_PIMPL(dedicated_worker_global_scope);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto post_message(ext::any&& message, ext::vector_span<void*> transfer) -> void;
    auto post_message(ext::any&& message, detail::structured_serialize_options_t options = {}) -> void;
    auto close() -> void;

public js_properties:
    DEFINE_GETTER(name, ext::string_view);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_WORKERS_DEDICATED_WORKER_GLOBAL_SCOPE_HPP
