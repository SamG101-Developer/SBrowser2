#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INDEXED_DB_IDB_FACTORY_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INDEXED_DB_IDB_FACTORY_HPP

#include "dom_object.hpp"
namespace indexed_db {class idb_factory;}

#include "ext/any.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"
#include <future>
namespace indexed_db {class idb_open_request;}

class indexed_db::idb_factory
        : public virtual dom_object
{
public js_methods:
    auto open(const ext::string& name, const ext::number<ulonglong>& version) -> idb_open_request;
    auto delete_database(const ext::string& name) -> idb_open_request;
    auto databases() -> std::promise<ext::vector<ext::map<ext::string, ext::any>>>;
    auto cmp(const ext::any& first, const ext::any& second) -> ext::number<short>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INDEXED_DB_IDB_FACTORY_HPP
