#include "history.hpp"
#include "history_private.hpp"

#include "javascript/environment/realms.hpp"

#include "dom/_typedefs.hpp"
#include "dom/detail/exception_internals.hpp"
#include "dom/detail/node_internals.hpp"
#include "dom/nodes/window.hpp"
#include "dom/nodes/window_private.hpp"


auto html::other::history::get_length() const -> ext::number<ulong>
{
    ACCESS_PIMPL(const history);
    using enum dom::detail::dom_exception_error_t;

    auto e = js::env::env::relevant(this);
    decltype(auto) window = e.cpp.global<dom::nodes::window*>();

    dom::detail::throw_v8_exception<SECURITY_ERR>(
            BIND_BACK(dom::detail::is_document_fully_active, window->d_func()->document.get()),
            u8"Document must be fully active");

    return d->length;
}
