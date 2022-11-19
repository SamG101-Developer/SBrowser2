#include "dom_object.hpp"
#include "dom_object_private.hpp"


dom_object::dom_object()
{
    INIT_PIMPL(dom_object);
}


auto dom_object::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<dom_object>{isolate}.auto_wrap_objects();
    return std::move(conversion);
}


dom_object::operator ext::string() const
{
    return u"";
}
