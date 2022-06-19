#include "abort_controller.hpp"

#include <web_apis/dom/detail/aborting_internals.hpp>


dom::abort::abort_controller::abort_controller():
        signal(nullptr)
{
    // create an abort controller
}


auto dom::abort::abort_controller::abort(
        ext::any_view reason)
        const -> void
{
    // abort the signal with the reason
    detail::aborting_internals::signal_abort(signal, reason);
}


auto dom::abort::abort_controller::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<abort_controller>{isolate}
            .ctor<>()
            .inherit<dom_object>()
            .function("abort", &abort_controller::abort)
            .var("signal", &abort_controller::signal, true)
            .auto_wrap_objects();
}
