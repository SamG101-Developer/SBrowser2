#pragma once
#ifndef SBROWSER2_ABORT_SIGNAL_HPP
#define SBROWSER2_ABORT_SIGNAL_HPP

#include "dom/nodes/event_target.hpp"
namespace dom::abort {class abort_signal;}


#include "ext/any.hpp"
#include "ext/functional.hpp"
#include "ext/optional.hpp"
#include "ext/type_traits.hpp"
#include "dom/abort/abort_signal_private.hpp"
namespace dom::nodes {class event_target;}


class dom::abort::abort_signal final
        : public nodes::event_target
{
public constructors:
    DOM_CTORS(abort_signal);
    MAKE_PIMPL(abort_signal);
    MAKE_V8_AVAILABLE;

public js_methods:
    static auto abort(const ext::optional<ext::any>& reason) -> abort_signal;
    static auto timeout(ext::number<ulonglong> milliseconds) -> abort_signal;
    auto throw_if_aborted() -> void;

private js_properties:
    DEFINE_GETTER(aborted, ext::boolean);
    DEFINE_GETTER(reason, ext::any);
};


#endif //SBROWSER2_ABORT_SIGNAL_HPP
