#include "abort_signal.hpp"

#include "javascript/environment/realms_2.hpp"

#include "dom/detail/aborting_internals.hpp"
#include "dom/detail/exception_internals.hpp"
#include "dom/detail/observer_internals.hpp"
#include "dom/other/dom_exception.hpp"

#include "html/detail/task_internals.hpp"



dom::abort::abort_signal::abort_signal()
        : INIT_PIMPL
        , reason{ext::nullopt}
{
    // create an abort signal
    bind_get(aborted);
}


auto dom::abort::abort_signal::abort(
        const ext::optional<ext::any>& reason)
        -> abort_signal
{
    // create a signal, mark it as aborted by giving it a reason, and return it
    auto signal = abort_signal{};
    signal.d_ptr->abort_reason = reason.value_or(other::dom_exception{"", ABORT_ERR});
    return signal;
}


auto dom::abort::abort_signal::timeout(
        ext::number<ulonglong> milliseconds)
        -> abort_signal
{
    // create a signal, and abort it after a timer has executed (TODO https://dom.spec.whatwg.org/#dom-abortsignal-timeout)
    auto signal = abort_signal{};
    JS_REALM_GET_RELEVANT(signal);

    auto timeout_error_callback = [] {detail::throw_v8_exception_formatted<TIMEOUT_ERR>();};
    auto callback =
            [signal_relevant_global_object, callback = std::move(timeout_error_callback)] mutable
            {detail::queue_global_task(html::detail::timer_task_source, signal_relevant_global_object, std::move(callback));};

    html::detail::run_steps_after_timeout(signal_relevant_global_object, "AbortSignal-timeout", milliseconds, callback);

    // return the signal
    return signal;
}


auto dom::abort::abort_signal::throw_if_aborted()
        -> void
{
    // if the reason attribute has been set, throw a v8 exception
    detail::throw_v8_exception_formatted<ABORT_ERR>(
            [this] {return detail::is_signal_aborted(this);},
            d_ptr->abort_reason);
}


auto dom::abort::abort_signal::get_aborted() const -> decltype(this->aborted)::value_t
{return detail::is_signal_aborted(this);}


auto dom::abort::abort_signal::get_reason() const -> decltype(this->reason)::value_t
{return d_ptr->abort_reason;}


auto dom::abort::abort_signal::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<abort_signal>{isolate}
            .inherit<event_target>()
            .function("timeout", &abort_signal::timeout)
            .function("abort", &abort_signal::abort)
            .function("throwIfAborted", &abort_signal::throw_if_aborted)
            .var("aborted", &abort_signal::aborted, true)
            .var("reason", &abort_signal::reason, false)
            .auto_wrap_objects();

    return std::move(conversion);
}
