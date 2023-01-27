module;
#include "ext/macros.hpp"


export module apis.indexed_db.idb_request:p;
import apis.dom.event_target;

import apis.indexed_db.types;


DEFINE_PRIVATE_CLASS(indexed_db, idb_request)
        : dom::event_target_private
{
public:
    MAKE_QIMPL(idb_request);

public:
    std::unique_ptr<detail::request_t> request;
};
