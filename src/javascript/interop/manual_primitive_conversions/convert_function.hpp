#ifndef SBROWSER2_CONVERT_FUNCTION_HPP
#define SBROWSER2_CONVERT_FUNCTION_HPP

#include "ext/boolean.hpp"
#include "ext/functional.hpp"
#include <v8pp/convert.hpp>


template <typename ...Ts> // NOTE: Each Ts == R(T...)
struct v8pp::convert<ext::function<Ts...>>
{
    using from_type = ext::function<Ts...>;
    using to_type = v8::Handle<v8::Function>; // TODO : v8::Handle? https://github.com/pmed/v8pp/issues/18#issuecomment-138602049

    static auto is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean;
    static auto from_v8(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> from_type;
    static auto to_v8(v8::Isolate* isolate, const from_type& cpp_value) -> to_type;
};


template <typename ...Ts>
auto v8pp::convert<ext::function<Ts...>>::is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean
{
    return not v8_value.IsEmpty() && v8_value->IsFunction();
}


template <typename ...Ts>
auto v8pp::convert<ext::function<Ts...>>::from_v8(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> from_type
{
    if (!is_valid(isolate, v8_value))
        throw std::invalid_argument{"Invalid type for converting to callable<_Tx> from v8"};

    v8::HandleScope javascript_scope{isolate};

    // TODO : conversion to ext::function<Ts...>
}


template <typename ...Ts>
auto v8pp::convert<ext::function<Ts...>>::to_v8(v8::Isolate* isolate, const from_type& cpp_value) -> to_type
{
    v8::EscapableHandleScope javascript_scope{isolate};

    auto v8_value = v8::Function::New(isolate->GetCurrentContext(), cpp_value).ToLocalChecked();
    return javascript_scope.template Escape(v8_value);
}


#endif //SBROWSER2_CONVERT_FUNCTION_HPP
