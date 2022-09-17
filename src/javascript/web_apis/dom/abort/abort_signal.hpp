#pragma once
#ifndef SBROWSER2_ABORT_SIGNAL_HPP
#define SBROWSER2_ABORT_SIGNAL_HPP

#include "dom/nodes/event_target.hpp"
namespace dom::abort {class abort_signal;}

#include "ext/functional.hpp"
#include "ext/optional.hpp"
#include "ext/type_traits.hpp"
namespace dom::nodes {class event_target;}
namespace dom::detail {auto signal_abort(abort::abort_signal*, const ext::any&) -> void;}
namespace dom::detail {auto follow_signal(abort::abort_signal*, abort::abort_signal*) -> void;}


class dom::abort::abort_signal final
        : public nodes::event_target
{
public aliases:
    using abort_signal_callback_t  = ext::function<void()>;
    using abort_signal_callbacks_t = ext::vector<abort_signal_callback_t>;

public friends:
    friend class nodes::event_target;

    friend auto dom::detail::signal_abort(
            abort::abort_signal* signal, const ext::any& reason) -> void;

    friend auto dom::detail::follow_signal(
            abort::abort_signal* following_signal, abort::abort_signal* parent_signal) -> void;

public constructors:
    DOM_CTORS(abort_signal);
    abort_signal();

public js_methods:
    static auto abort(const ext::optional<ext::any>& reason) -> abort_signal;
    static auto timeout(ext::number<ulonglong> milliseconds) -> abort_signal;
    auto throw_if_aborted() -> void;

public js_properties:
    ext::property<ext::boolean> aborted;
    ext::property<ext::any> reason;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

private cpp_properties:
    abort_signal_callbacks_t m_abort_algorithms;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(aborted);
};


#endif //SBROWSER2_ABORT_SIGNAL_HPP
