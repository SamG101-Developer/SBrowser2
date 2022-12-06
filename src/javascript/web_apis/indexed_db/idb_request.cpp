#include "idb_request.hpp"

#include "dom/detail/exception_internals.hpp"

#include "dom/other/dom_exception.hpp"


indexed_db::idb_request::idb_request()
{
    bind_get(result);
    bind_get(error);
    bind_get(ready_state);
}


auto indexed_db::idb_request::get_result()
        const -> ext::any
{
    // throw an invalid state exception if the transaction hasn't finished yet, because not all the data will be ready
    // in the 'result' attribute - once the request is completed the 'm_done_flag' will be set to true
    dom::detail::exception_internals::throw_v8_exception_formatted<INVALID_STATE_ERR>(
            [this] {return !m_done_flag;},
            "Request hasn't finished yet");

    // return all the data once the request has completed
    property_guard(result);
    return *result;
}


auto indexed_db::idb_request::get_error()
        const -> dom::other::dom_exception
{
    // throw an invalid state exception if the transaction hasn't finished yet, because there may be an error in future
    // data that will be processed in this request, but hasn't been reached yet - once the request is completed the
    // 'm_done_flag' will be set to true
    dom::detail::exception_internals::throw_v8_exception_formatted<INVALID_STATE_ERR>(
            [this] {return !m_done_flag;},
            "Request hasn't finished yet");

    // return the error once the request has completed
    property_guard(error);
    return dom::other::dom_exception{(*error).message(), (*error).type()};
}


auto indexed_db::idb_request::get_ready_state()
        const -> idb_request_ready_state
{
    // if the request is done (determined by the 'm_done_flag'), then return DONE, otherwise PENDING
    using enum idb_request_ready_state;
    return m_done_flag ? DONE : PENDING;
}


auto indexed_db::idb_request::get_the_parent(
        dom::events::event* event)
        -> dom::nodes::event_target*
{
    // the event traversal parent of an IDBRequest is the associated IDBTransaction
    return transaction;
}


auto indexed_db::idb_request::to_v8(
        v8::Isolate* isolate) const &&
        -> ext::any
{
    return v8pp::class_<idb_request>{isolate}
            .inherit<dom::nodes::event_target>()
            .var("result", &idb_request::result, true)
            .var("error", &idb_request::error, true)
            .var("source", &idb_request::source, true)
            .var("transaction", &idb_request::transaction, true)
            .var("readyState", &idb_request::ready_state, true);
}
