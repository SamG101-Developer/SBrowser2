#include "abort_signal.hpp"
#include "abort_signal_private.hpp"

#include "javascript/environment/realms_2.hpp"

#include "dom/detail/aborting_internals.hpp"
#include "dom/detail/exception_internals.hpp"
#include "dom/detail/observer_internals.hpp"
#include "dom/other/dom_exception.hpp"
#include "dom/other/dom_exception_private.hpp"

#include "html/detail/task_internals.hpp"


dom::abort::abort_signal::abort_signal()
{
    INIT_PIMPL(abort_signal);
}


auto dom::abort::abort_signal::abort(
        ext::optional<ext::any>&& reason)
        -> abort_signal
{
    using enum dom::detail::dom_exception_error_t;

    // Create a new AbortSignal (on the stack - not a node-like object), and mark it as aborted by giving it a 'reason';
    // this reason is either the 'reason' parameter, or a ABORT_ERR DomException object. Return the newly created signal
    // that is pre-aborted.
    auto signal = abort_signal{};
    signal.d_func()->abort_reason = std::move(reason).value_or(other::dom_exception{u8"", ABORT_ERR});
    return signal;
}


auto dom::abort::abort_signal::timeout(ext::number<ulonglong> milliseconds) -> abort_signal
{
    using enum dom::detail::dom_exception_error_t;

    // Create a new AbortSignal (on the stack - not a node-like object), and access the relevant Realm to the newly
    // created AbortSignal.
    auto signal = abort_signal{};
    JS_REALM_GET_RELEVANT(signal);

    // Create the 'timeout_error_callback' - this callback will throw a TIMEOUT_ERR DomException. Set the 'callback'
    // (which will be executed after the time) so queue a global task that will execute the 'callback' in the
    // AbortSignal's relevant global object, and in the timer task source (non-blocking to dom manipulation).
    auto timeout_error_callback = [] {detail::throw_v8_exception<TIMEOUT_ERR>();};
    auto callback =
            [signal_relevant_global_object, callback = std::move(timeout_error_callback)] mutable
            {detail::queue_global_task(html::detail::timer_task_source, signal_relevant_global_object, std::move(callback));};

    // Run the 'callback' after the timer has finished ('milliseconds' milliseconds timeout), and execute it in the
    // AbortSignal's relevant global object.
    html::detail::run_steps_after_timeout(signal_relevant_global_object, u8"AbortSignal-timeout", milliseconds, callback);

    // Return the newly created AbortSignal
    return signal;
}


auto dom::abort::abort_signal::throw_if_aborted() -> void
{
    ACCESS_PIMPL(abort_signal);
    using enum dom::detail::dom_exception_error_t;

    // If the 'reason' attribute has been set, throw a ABORT_ERR DomException, whose message is the DomException message
    // stored in the 'reason' - the exception is effectively recreated, but into the 'throw_...' method, so it is
    // created and thrown at the correct time.
    detail::throw_v8_exception<ABORT_ERR>(
            [this] {return detail::is_signal_aborted(this);},
            d->abort_reason.to<dom::other::dom_exception>().d_func()->message);
}


auto dom::abort::abort_signal::get_aborted() const -> ext::boolean
{
    // The 'aborted' getter returns 'true' if the signal has aborted - this is checked by chekcing if the 'reason'
    // attribute is empty (=> not-aborted) or not (=> aborted).
    ACCESS_PIMPL(const abort_signal);
    return d->aborted();
}


auto dom::abort::abort_signal::get_reason() const -> ext::any
{
    // The 'reason' getter returns the equivalent 'reason' attribute value that is stored in the private class.
    ACCESS_PIMPL(const abort_signal);
    return d->abort_reason;
}


auto dom::abort::abort_signal::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<abort_signal>{isolate}
        .inherit<event_target>()
        .function("timeout", &abort_signal::timeout)
        .function("abort", &abort_signal::abort)
        .function("throwIfAborted", &abort_signal::throw_if_aborted)
        .property("aborted", &abort_signal::get_aborted)
        .property("reason", &abort_signal::get_reason)
        .auto_wrap_objects();

    return std::move(conversion);
}
