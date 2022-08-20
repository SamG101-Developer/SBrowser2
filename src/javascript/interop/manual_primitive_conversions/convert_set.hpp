#ifndef SBROWSER2_CONVERT_SET_HPP
#define SBROWSER2_CONVERT_SET_HPP

#include <ext/set.hpp>
#include <v8-container.h>
#include <v8pp/convert.hpp>


template <typename _Tx>
struct v8pp::convert<ext::set<T>>
{
    using from_type = ext::set<T>;
    using to_type = v8::Local<v8::Set>;

    auto static is_valid(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> ext::boolean {return not v8_value.IsEmpty() && v8_value->IsSet();}
    auto static from_v8(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> from_type;
    auto static to_v8(v8::Isolate* isolate, const from_type& cpp_value_datetime_object) -> to_type;
};


template <typename _Tx>
inline auto v8pp::convert<ext::set<T>>::from_v8(v8::Isolate* isolate, v8::Local<v8::Value> v8_value) -> from_type
{
    if (not is_valid(isolate, v8_value)) throw std::invalid_argument{"Invalid type for converting to ext::set<_Tx> from v8"};
    v8::HandleScope javascript_scope{isolate};

    // save the current context
    auto v8_context          = isolate->GetCurrentContext();
    auto v8_value_set        = v8_value.template As<v8::Set>();
    auto v8_value_set_length = v8_value_set->Size();
    from_type cpp_value_set;

    // iterate through the numeric positions of the values, in the v8 set
    for (auto v8_value_set_key_index = 0; v8_value_set_key_index < v8_value_set_length; ++v8_value_set_key_index)
    {
        // get the value from the index
        auto v8_value_set_val = v8_value_set->Get(v8_context, v8_value_set_key_index);

        // convert the value to a cpp value, and save it back into the cpp set
        auto cpp_value_set_val = v8pp::convert<T>::from_v8(isolate, v8_value_set_val);
        cpp_value_set.insert(cpp_value_set_val);
    }

    return cpp_value_set;
}


template <typename _Tx>
inline auto v8pp::convert<ext::set<T>>::to_v8(v8::Isolate* isolate, const from_type& cpp_value_set) -> to_type
{
    v8::EscapableHandleScope javascript_scope{isolate};

    // save the current context
    auto v8_context   = isolate->GetCurrentContext();
    auto v8_value_set = v8::Set::New(isolate);

    // iterate through the values in the cpp set
    for (const auto& cpp_value_set_val: cpp_value_set)
    {
        // convert the value to v8 a value, and save it back into the v8 set
        auto v8_value_set_val = v8pp::convert<T>::to_v8(isolate, cpp_value_set_val);
        v8_value_set->Add(v8_context, v8_value_set_val);
    }

    return javascript_scope.template Escape(v8_value_set);
}


template <typename _Tx>
struct v8pp::is_wrapped_class<ext::set<T>> : std::false_type{};


#endif //SBROWSER2_CONVERT_SET_HPP
