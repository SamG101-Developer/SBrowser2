#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_WINDOW_OR_WORKER_GLOBAL_SCOPE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_WINDOW_OR_WORKER_GLOBAL_SCOPE_HPP

#include "dom_object.hpp"
namespace html::mixins {class window_or_worker_global_scope;}
namespace html::mixins {class window_or_worker_global_scope_private;}

#include INCLUDE_INNER_TYPES(html)
namespace indexed_db {class idb_factory;}
namespace service_workers::caches {class cache_storage;}
namespace web_crypto {class crypto;}


class html::mixins::window_or_worker_global_scope
        : public virtual dom_object
{
public constructors:
    MAKE_PIMPL(window_or_worker_global_scope);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto report_error(ext::any e) -> void;
    auto btoa(ext::string_view data) -> ext::string;
    auto atob(ext::string_view data) -> ext::byte_string;

private js_properties:
    /* [INDEX-DB] */
    DEFINE_GETTER(indexed_db, indexed_db::idb_factory*);

    /* [SERVICE-WORKERS] */
    DEFINE_GETTER(cache, service_workers::caches::cache_storage);

    /* [WEB-CRYPTO] */
    DEFINE_GETTER(crypto, web_crypto::crypto*);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_WINDOW_OR_WORKER_GLOBAL_SCOPE_HPP
