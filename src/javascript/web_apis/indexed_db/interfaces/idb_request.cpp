module;
#include "ext/macros.hpp"


module apis.indexed_db.idb_request;


auto indexed_db::idb_request::get_result() const -> ext::any
{
    dom::detail::throw_exception<INVALID_STATE_ERR>(
            [] {return d->request->done_flag;},
            u"Can't get result of done request", js::env::relevant(this));

    ACCESS_PIMPL;
    return d->request->result;
}
