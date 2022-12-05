module;
#include "ext/macros/pimpl.hpp"
#include "javascript/macros/expose.hpp"
#include <tuplet/tuple.hpp>
#include <v8-isolate.h>
#include <v8pp/class.hpp>

module apis.dom_object;
import apis.dom_object_private;
import ext.tuple;
import ext.string;
import js.env.module_type;


dom_object::dom_object()
{
    INIT_PIMPL(dom_object);
}


auto dom_object::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT;
    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}


dom_object::operator ext::string() const
{
    return u"";
}
