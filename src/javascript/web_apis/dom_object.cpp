#include "dom_object.hpp"
#include "dom_object_private.hpp"


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
