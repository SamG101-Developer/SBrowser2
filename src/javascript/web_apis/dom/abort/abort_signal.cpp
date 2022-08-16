#include "abort_signal.hpp"

#include "javascript/environment/realms_2.hpp"
#include "dom/detail/exception_internals.hpp"
#include "dom/detail/observer_internals.hpp"
#include "dom/other/dom_exception.hpp"


dom::abort::abort_signal::abort_signal()
        : reason{ext::nullopt}
{
    // create an abort signal
}


auto dom::abort::abort_signal::abort(
        const ext::optional<ext::any>& reason)
        -> abort_signal
{
    // create a signal, mark it as aborted by giving it a reason, and return it
    abort_signal signal;
    signal.reason = reason.value_or(other::dom_exception{"", ABORT_ERR});
    return signal;
}


auto dom::abort::abort_signal::timeout(
        const ext::number<ulonglong>& milliseconds)
        -> abort_signal
{
    // create a signal, and abort it after a timer has executed (TODO https://dom.spec.whatwg.org/#dom-abortsignal-timeout)
    abort_signal signal;
    JS_REALM_GET_RELEVANT(signal)

    auto timeout_error_callback = [] {detail::throw_v8_exception_formatted<TIMEOUT_ERR>();};
    auto callback = [&signal_relevant_global_object, timeout_error_callback] {detail::queue_global_task(html::detail::timer_task_source(), signal_relevant_global_object, timeout_error_callback);};
    html::detail::run_steps_after_timeout(signal_relevant_global_object, "AbortSignal-timeout", milliseconds, callback);

    // return the signal
    return signal;
}


auto dom::abort::abort_signal::throw_if_aborted()
        -> void
{
    // if the reason attribute has been set, throw a v8 exception
    detail::throw_v8_exception_formatted<ABORT_ERR>(
            [this] {return reason().to<ext::boolean>();},
            reason().to<other::dom_exception>().message());
}


auto dom::abort::abort_signal::get_aborted()
        const -> ext::boolean
{
    // the signal has aborted if the reason attribute has been set
    return reason().has_value();
}


auto dom::abort::abort_signal::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<abort_signal>{isolate}
            .inherit<event_target>()
            .function("timeout", &abort_signal::timeout)
            .function("abort", &abort_signal::abort)
            .function("throwIfAborted", &abort_signal::throw_if_aborted)
            .var("aborted", &abort_signal::aborted, true)
            .var("reason", &abort_signal::reason, false)
            .auto_wrap_objects();
}
