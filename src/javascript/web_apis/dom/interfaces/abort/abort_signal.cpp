module;
#include "ext/macros.hpp"
#include <tl/optional.hpp>


module apis.dom.abort_signal;
import apis.dom.dom_exception;
import apis.dom.detail;
import apis.dom.types;

import ext.core;
import js.env.module_type;
import js.env.realms;


dom::abort_signal::abort_signal()
{
    INIT_PIMPL;
}


auto dom::abort_signal::abort(ext::optional<ext::any>&& reason) -> std::unique_ptr<abort_signal>
{
    using enum dom::detail::dom_exception_error_t;

    // Create a new AbortSignal (on the stack - not a node-like object), and mark it as aborted by giving it a 'reason';
    // this reason is either the 'reason' parameter, or a ABORT_ERR DomException object. Return the newly created signal
    // that is pre-aborted.
    auto signal = std::make_unique<abort_signal>();
    signal->d_func()->abort_reason = std::move(reason).value_or(dom_exception{u8"", ABORT_ERR});
    return std::move(signal);
}


auto dom::abort_signal::timeout(ext::number<ulonglong> milliseconds) -> std::unique_ptr<abort_signal>
{
    using enum dom::detail::dom_exception_error_t;

    // Create a new AbortSignal (on the stack - not a node-like object), and access the relevant Realm to the newly
    // created AbortSignal.
    auto signal = std::make_unique<abort_signal>();
    auto e = js::env::env::relevant(signal.get());

    // Create the 'timeout_error_callback' - this callback will throw a TIMEOUT_ERR DomException. Set the 'callback'
    // (which will be executed after the time) so queue a global task that will execute the 'callback' in the
    // AbortSignal's relevant global object, and in the timer task source (non-blocking to dom manipulation).
    auto timeout_error_callback = [] {detail::throw_v8_exception<TIMEOUT_ERR>();};
    auto callback =
            [&e, callback = std::move(timeout_error_callback)] mutable
            {detail::queue_global_task(html::detail::timer_task_source, e.js.global(), std::move(callback));};

    // Run the 'callback' after the timer has finished ('milliseconds' milliseconds timeout), and execute it in the
    // AbortSignal's relevant global object.
    html::detail::run_steps_after_timeout(e.js.global(), u"AbortSignal-timeout", milliseconds, callback);

    // Return the newly created AbortSignal
    return signal;
}


auto dom::abort_signal::throw_if_aborted() -> void
{
    ACCESS_PIMPL;
    using enum dom::detail::dom_exception_error_t;

    // If the 'reason' attribute has been set, throw a ABORT_ERR DomException, whose message is the DomException message
    // stored in the 'reason' - the exception is effectively recreated, but into the 'throw_...' method, so it is
    // created and thrown at the correct time.
    detail::throw_v8_exception<ABORT_ERR>(
            [d] {return d->aborted();},
            d->abort_reason.to<dom_exception>().d_func()->message);
}


auto dom::abort_signal::get_aborted() const -> ext::boolean
{
    // The 'aborted' getter returns 'true' if the signal has aborted - this is checked by chekcing if the 'reason'
    // attribute is empty (=> not-aborted) or not (=> aborted).
    ACCESS_PIMPL;
    return d->aborted();
}


auto dom::abort_signal::get_reason() const -> ext::any
{
    // The 'reason' getter returns the equivalent 'reason' attribute value that is stored in the private class.
    ACCESS_PIMPL;
    return d->abort_reason;
}


auto dom::abort_signal::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<event_target>()
        .function("timeout", &abort_signal::timeout)
        .function("abort", &abort_signal::abort)
        .function("throwIfAborted", &abort_signal::throw_if_aborted)
        .property("aborted", &abort_signal::get_aborted)
        .property("reason", &abort_signal::get_reason)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
