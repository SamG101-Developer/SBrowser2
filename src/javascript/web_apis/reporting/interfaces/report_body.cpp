module;
#include "ext/macros.hpp"


module apis.reporting.report_body;

import ext.core;
import js.env.module_type;


reporting::report_body::report_body()
{
    INIT_PIMPL;
}


auto reporting::report_body::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .function("toJSON", &report_body::operator ext::string)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}


reporting::report_body::operator ext::string() const
{
    return web_idl::detail::default_json_steps(this);
}
