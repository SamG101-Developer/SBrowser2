#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INDEXED_DB_IDB_REQUEST_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INDEXED_DB_IDB_REQUEST_HPP

#include "dom/nodes/event_target.hpp"
namespace indexed_db {class idb_request;}

#include "dom/other/dom_exception.hpp"
namespace indexed_db {class idb_cursor;}
namespace indexed_db {class idb_index;}
namespace indexed_db {class idb_object_store;}
namespace indexed_db {class idb_transaction;}

class indexed_db::idb_request
        : public dom::nodes::event_target
{
public enums:
    enum class idb_request_ready_state {PENDING, DONE};

public constructors:
    idb_request();

public cpp_properties:
    ext::property<ext::any> result;
    ext::property<dom::other::dom_exception> error;
    ext::property<ext::variant<std::unique_ptr<idb_object_store>, std::unique_ptr<idb_index>, std::unique_ptr<idb_cursor>>> source;
    ext::property<idb_transaction*> transaction;
    ext::property<idb_request_ready_state> ready_state;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

protected cpp_methods:
    auto get_the_parent(dom::events::event* event) -> dom::nodes::event_target* override;

private cpp_properties:
    ext::boolean m_done_flag;
    ext::boolean m_processed_flag;

private js_properties:
    _EXT_NODISCARD auto get_result() const -> ext::any;
    _EXT_NODISCARD auto get_error() const -> dom::other::dom_exception;
    _EXT_NODISCARD auto get_ready_state() const -> idb_request_ready_state;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INDEXED_DB_IDB_REQUEST_HPP
