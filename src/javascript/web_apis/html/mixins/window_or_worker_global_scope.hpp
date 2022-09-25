#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_WINDOW_OR_WORKER_GLOBAL_SCOPE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_WINDOW_OR_WORKER_GLOBAL_SCOPE_HPP

#include "dom_object.hpp"
namespace html::mixins {class window_or_worker_global_scope;}

namespace indexed_db {class idb_factory;}
namespace service_workers::caches {class cache_storage;}
namespace web_crypto {class crypto;}


class html::mixins::window_or_worker_global_scope
        : public virtual dom_object
{
private js_properties:
    /* INDEX_DB */
    ext::property<indexed_db::idb_factory*> indexed_db;

    /* SERVICE_WORKERS */
    ext::property<std::unique_ptr<service_workers::caches::cache_storage>> caches;

    /* WEB_CRYPTO */
    ext::property<std::unique_ptr<web_crypto::crypto>> crypto;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_WINDOW_OR_WORKER_GLOBAL_SCOPE_HPP
