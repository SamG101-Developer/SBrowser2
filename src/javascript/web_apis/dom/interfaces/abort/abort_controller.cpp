module;
#include "ext/macros.hpp"


module apis.dom.abort_controller;
import apis.dom.abort_signal;

import ext.core;
import js.env.module_type;


dom::abort_controller::abort_controller()
{
    INIT_PIMPL;
}


auto dom::abort_controller::abort(ext::any&& reason) const -> void
{
    // Abort the signal with the reason, by calling the detail 'signal_abort' method on the signal that this controller
    // stores in a unique_ptr in the private class. Move the reason into the method.
    ACCESS_PIMPL;
    d->signal->abort(std::move(reason));
}


auto dom::abort_controller::get_signal() const -> abort_signal*
{
    // Get the signal being stored in the unique_ptr in the private class, by calling the .get() method to access the
    // raw pointer.
    ACCESS_PIMPL;
    return d->signal.get();
}


auto dom::abort_controller::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .ctor<>()
        .function("abort", &abort_controller::abort)
        .property("signal", &abort_controller::get_signal)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
