module;
#include "ext/macros.hpp"


module apis.indexed_db.idb_request;

import apis.dom.dom_exception;
import apis.dom.detail;
import apis.dom.types;

import js.env.realms;
import ext.core;


auto indexed_db::idb_request::get_result() const -> ext::any
{
    ACCESS_PIMPL;
    using enum dom::detail::dom_exception_error_t;

    dom::detail::throw_v8_exception<INVALID_STATE_ERR>([d] {return d->request->done_flag;}, u"Can't get result of done request", js::env::env::relevant(this));

    return d->request->result;
}
