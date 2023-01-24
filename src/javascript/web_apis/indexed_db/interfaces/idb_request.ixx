module;
#include "ext/macros.hpp"


export module apis.indexed_db.idb_request;
import apis.dom.event_target;

import apis.indexed_db.types;


DEFINE_PUBLIC_CLASS(indexed_db, idb_request)
        : public dom::event_target
{
public constructors:
    idb_request();
    MAKE_PIMPL(idb_request);
    MAKE_V8_AVAILABLE(WINDOW | WORKER);

public js_properties:
    DEFINE_GETTER(result, ext::any);
    DEFINE_GETTER(error, dom::dom_exception);
    DEFINE_GETTER(source, ext::variant<idb_object_store*, idb_index*, idb_cursor*>);
    DEFINE_GETTER(transaction, idb_transaction*);
    DEFINE_GETTER(ready_state, detail::idb_request_ready_state);
};
