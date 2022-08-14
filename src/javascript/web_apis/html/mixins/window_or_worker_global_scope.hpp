#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_WINDOW_OR_WORKER_GLOBAL_SCOPE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_WINDOW_OR_WORKER_GLOBAL_SCOPE_HPP

#include "dom_object.hpp"
namespace html::mixins {class window_or_worker_global_scope;}

namespace indexed_db {class idb_factory;}


class html::mixins::window_or_worker_global_scope
        : public dom_object
{
public js_properties:
    /* INDEX_DB */
    ext::property<indexed_db::idb_factory*> indexed_db;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_WINDOW_OR_WORKER_GLOBAL_SCOPE_HPP
