#ifndef SBROWSER2_DOM_OBJECT_HPP
#define SBROWSER2_DOM_OBJECT_HPP

#include <ext/any.hpp>
#include <ext/keywords.hpp>
#include <v8-isolate.h>
#include <v8pp/class.hpp>

namespace web_apis {class dom_object;}


class web_apis::dom_object
{
public cpp_methods:
    virtual auto to_v8(v8::Isolate* isolate) const && -> ext::any = 0;
};


inline auto web_apis::dom_object::to_v8(v8::Isolate* isolate) const && -> ext::any
{
    return v8pp::class_<dom_object>{isolate}.auto_wrap_objects();
}


#endif //SBROWSER2_DOM_OBJECT_HPP
