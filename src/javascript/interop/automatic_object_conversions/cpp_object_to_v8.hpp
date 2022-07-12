#ifndef SBROWSER2_CPP_OBJECT_TO_V8_HPP
#define SBROWSER2_CPP_OBJECT_TO_V8_HPP

#include <type_traits>
#include <v8-isolate.h>
#include <v8pp/class.hpp>

namespace javascript::interop {template <typename T> auto cpp_object_to_v8(v8::Isolate* isolate) -> v8pp::class_<T>;}


template <typename T> // TODO : `typename` -> `inherit<web_apis::dom_object> T>`
auto javascript::interop::cpp_object_to_v8(v8::Isolate* isolate) -> v8pp::class_<T>
{
    // get the v8 conversion of the class cby calling the conversion method on a temporary object of type T
    return T{}.to_v8(isolate).template to<v8pp::class_<T>>();
}


#endif //SBROWSER2_CPP_OBJECT_TO_V8_HPP
