#include "history.hpp"
#include "history_private.hpp"

#include "dom/_typedefs.hpp"
#include "dom/detail/exception_internals.hpp"
#include "dom/detail/node_internals.hpp"
#include "dom/nodes/window.hpp"
#include "dom/nodes/window_private.hpp"


auto html::other::history::get_length() const -> ext::number<ulong>
{
    ACCESS_PIMPL(const history);
    using enum dom::detail::dom_exception_error_t;

    JS_REALM_GET_RELEVANT(this);
    decltype(auto) window = v8pp::from_v8<dom::nodes::window*>(this_relevant_agent, this_relevant_global_object);

    dom::detail::throw_v8_exception<SECURITY_ERR>(
            BIND_BACK(dom::detail::is_document_fully_active, window->d_func()->document.get()),
            u8"Document must be fully active");

    return d->length;
}
