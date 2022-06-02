#ifndef SBROWSER2_CONVERT_VECTOR_LIKE_HPP
#define SBROWSER2_CONVERT_VECTOR_LIKE_HPP

#include <ext/vector_like.hpp>
#include <v8-container.h>
#include <v8pp/convert.hpp>


template <typename T>
struct v8pp::convert<ext::vector_like<T>>
{
    using from_type = ext::vector_like<T>;
    using to_type   = v8::Local<v8::Object>;

    auto static is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean {return not v8_value.IsEmpty() and v8_value->IsObject();}
    static auto from_v8(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> from_type;
    static auto to_v8(v8::Isolate* isolate, const from_type& cpp_value) -> to_type;
};


template <typename T>
inline auto v8pp::convert<ext::vector_like<T>>::from_v8(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> from_type
{
    if (not is_valid(isolate, v8_value)) throw std::invalid_argument{"Invalid type for converting to ext::vector_like from v8"}
}


#endif //SBROWSER2_CONVERT_VECTOR_LIKE_HPP
