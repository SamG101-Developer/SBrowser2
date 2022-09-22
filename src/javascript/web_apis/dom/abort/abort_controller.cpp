#include "abort_controller.hpp"

#include "dom/abort/abort_signal.hpp"
#include "dom/detail/aborting_internals.hpp"


dom::abort::abort_controller::abort_controller()
        : INIT_PIMPL
{
    // create an abort controller
}


auto dom::abort::abort_controller::abort(
        const ext::any& reason)
        const -> void
{
    // abort the signal with the reason
    detail::signal_abort(d_ptr->signal.get(), reason);
}


auto dom::abort::abort_controller::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<abort_controller>{isolate}
        .inherit<dom_object>()
        .ctor<>()
        .function("abort", &abort_controller::abort)
        .property("signal", &abort_controller::get_signal, true)
        .auto_wrap_objects();

    return std::move(conversion);
}
