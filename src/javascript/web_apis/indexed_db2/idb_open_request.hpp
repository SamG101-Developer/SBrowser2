#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INDEXED_DB_IDB_OPEN_REQUEST_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INDEXED_DB_IDB_OPEN_REQUEST_HPP

#include "indexed_db/idb_request.hpp"
namespace indexed_db {class idb_open_request;}


class indexed_db::idb_open_request
        : public idb_request
{
protected cpp_methods:
    auto get_the_parent(dom::events::event *event) -> dom::nodes::event_target* override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INDEXED_DB_IDB_OPEN_REQUEST_HPP
