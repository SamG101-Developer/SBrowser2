#ifndef SBROWSER2_CPP_OBJECT_TO_V8_HPP
#define SBROWSER2_CPP_OBJECT_TO_V8_HPP

#include <type_traits>
#include <v8-isolate.h>
#include <v8pp/class.hpp>

#include <dom_object.hpp>

namespace javascript::interop {template <typename T> auto cpp_object_to_v8(v8::Isolate* isolate) requires std::is_base_of_v<T, webapis::dom_object>;}


template <typename T>
auto javascript::interop::cpp_object_to_v8(v8::Isolate* isolate) requires std::is_base_of_v<T, webapis::dom_object>
{
    // get the v8 conversion of the class by calling the conversion method on a temporary object of type T
    return T{}.v8(isolate).template to<v8pp::class_<T>>();
}


#endif //SBROWSER2_CPP_OBJECT_TO_V8_HPP
