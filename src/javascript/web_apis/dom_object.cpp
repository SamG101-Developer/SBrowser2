module;
#include <tuplet/tuple.hpp>
#include <v8-isolate.h>

module apis.dom_object;
import apis.dom_object_private;
import ext.tuple;
import ext.string;


dom_object::dom_object()
{
    INIT_PIMPL(dom_object);
}


auto dom_object::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT;
    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}


dom_object::operator ext::string() const
{
    return u"";
}
