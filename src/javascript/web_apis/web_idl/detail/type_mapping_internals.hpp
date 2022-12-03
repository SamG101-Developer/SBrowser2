#pragma once
#include "ext/concepts.ixx"
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_IDL_DETAIL_TYPE_MAPPING_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_IDL_DETAIL_TYPE_MAPPING_INTERNALS_HPP


#include "ext/array_buffer.hpp"
#include "ext/map.ixx"
#include "ext/optional.hpp"
#include "ext/promise.hpp"
#include "ext/span.hpp"
#include "ext/symbol.ixx"
#include "ext/type_traits.ixx"
#include <v8-forward.h>
class dom_object;


namespace web_idl::detail
{
    // template <typename T>
    // auto convert(v8::Isolate* isolate, v8::Local<v8::Value> V) -> T;
    //
    // template <> /* 3.2.1 - Any */
    // auto convert<ext::any>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::any;
    //
    // template <> /* 3.2.2 - Undefined (v8::Undefined -> void; v8::Null -> nullptr)*/
    // auto convert<void>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> void;
    //
    // template <> /* 3.2.3 - Boolean */
    // auto convert<ext::boolean>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::boolean;
    //
    // template <> /* 3.2.4.1 - Byte */
    // auto convert<ext::number<int8_t>>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::number<int8_t>;
    //
    // template <> /* 3.2.4.2 - Octet */
    // auto convert<ext::number<uint8_t>>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::number<uint8_t>;
    //
    // template <> /* 3.2.4.3 - Short */
    // auto convert<ext::number<int16_t>>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::number<int16_t>;
    //
    // template <> /* 3.2.4.4 - Unsigned short */
    // auto convert<ext::number<uint16_t>>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::number<uint16_t>;
    //
    // template <> /* 3.2.4.5 - Long */
    // auto convert<ext::number<int32_t>>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::number<int32_t>;
    //
    // template <> /* 3.2.4.6 - Unsigned long */
    // auto convert<ext::number<uint32_t>>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::number<uint32_t>;
    //
    // template <> /* 3.2.4.7 - Long long */
    // auto convert<ext::number<int64_t>>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::number<int64_t>;
    //
    // template <> /* 3.2.4.8 - Unsigned long long */
    // auto convert<ext::number<uint64_t>>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::number<uint64_t>;
    //
    // template <> /* 3.2.5 - Float */
    // auto convert<ext::number<float>>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::number<float>;
    //
    // template <> /* 3.2.6 - Unrestricted float */
    // auto convert<ext::number<float, true>>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::number<float, true>;
    //
    // template <> /* 3.2.7 - Double */
    // auto convert<ext::number<double>>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::number<double>;
    //
    // template <> /* 3.2.8 - Unrestricted double */
    // auto convert<ext::number<double, true>>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::number<double, true>;
    //
    // template <> /* 3.2.9 - BigInt */
    // auto convert<ext::number<bigint>>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::number<bigint>;
    //
    // template <> /* 3.2.10 / 3.2.11 / 3.2.12 - String */
    // auto convert<ext::string>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::string;
    //
    // template <> /* 3.2.13 - Object TODO : void*? */
    // auto convert<dom_object*>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> dom_object*;
    //
    // template <> /* 3.2.14 - Symbol */
    // auto convert<ext::symbol*>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::symbol*;
    //
    // // template <> /* 3.2.15 - Interface TODO */
    // // template <> /* 3.2.16 - Callback Interface TODO */
    // // template <> /* 3.2.17 - Dictionary TODO (ext::map<K, V>) */
    // // template <> /* 3.2.18 - Enums TODO */
    // // template <> /* 3.2.19 - Callback TODO (ext::function<Ts...>)? */
    // // template <> /* 3.2.20 - Nullable TODO (ext::optional<T>)? */
    // // template <> /* 3.2.21 - Sequence TODO (ext::vector<T>) */
    // // template <> /* 3.2.22 - Record TODO (const ext::map<K, V>)? */
    // // template <> /* 3.2.23 - Enums TODO (ext::promise<T>) */
    // // template <> /* 3.2.24 - Union TODO (ext::variant<Ts...>) */
    // template <> /* 3.2.25 - ArrayBuffer */
    // auto convert<ext::array_buffer>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::array_buffer;
    //
    // template <> /* 3.2.25 - DataView */
    // auto convert<ext::data_view>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::data_view;
    //
    // template <> /* 3.2.25 - int8_array */
    // auto convert<ext::int8_array>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::int8_array;
    //
    // template <> /* 3.2.25 - int16_array */
    // auto convert<ext::int16_array>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::int16_array;
    //
    // template <> /* 3.2.25 - int32_array */
    // auto convert<ext::int32_array>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::int32_array;
    //
    // template <> /* 3.2.25 - uint8_array */
    // auto convert<ext::uint8_array>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::uint8_array;
    //
    // template <> /* 3.2.25 - uint16_array */
    // auto convert<ext::uint16_array>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::uint16_array;
    //
    // template <> /* 3.2.25 - uint32_array */
    // auto convert<ext::uint32_array>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::uint32_array;
    //
    // template <> /* 3.2.25 - uint8_clamped_array */
    // auto convert<ext::uint8_clamped_array>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::uint8_clamped_array;
    //
    // template <> /* 3.2.25 - bigint64_array */
    // auto convert<ext::bigint64_array>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::bigint64_array;
    //
    // template <> /* 3.2.25 - biguint64_array */
    // auto convert<ext::biguint64_array>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::biguint64_array;
    //
    // template <> /* 3.2.25 - float32_array */
    // auto convert<ext::float32_array>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::float32_array;
    //
    // template <> /* 3.2.25 - float64_array */
    // auto convert<ext::float64_array>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::float64_array;

    /* 3.2.4.9 */
    template <ext::arithmetic T>
    auto integer_part(T&& value) -> long long;

    template <int BitLength, bool Signed>
    auto convert_to_int(v8::Local<v8::Number>) -> ext::number<std::conditional_t<Signed, int64_t, uint64_t>>;

    /* 3.2.23.1 */
    template <typename T>
    auto create_promise(v8::Local<v8::Context> realm) -> ext::promise<T>;

    template <typename T>
    auto create_resolved_promise(T&& x, v8::Local<v8::Context> realm) -> ext::promise<T>;

    auto create_resolved_promise(v8::Local<v8::Context> realm) -> ext::promise<void>;

    template <typename T>
    auto create_rejected_promise(ext::any reason, v8::Local<v8::Context> realm) -> ext::promise<T>;

    template <typename T>
    auto resolve_promise(ext::promise<T>& promise, v8::Local<v8::Context> realm, T&& x) -> ext::promise<T>&;

    auto resolve_promise(ext::promise<void>& promise, v8::Local<v8::Context> realm) -> ext::promise<void>&;

    template <typename T, typename U>
    auto reject_promise(ext::promise<T>& promise, v8::Local<v8::Context> realm, U&& reason) -> ext::promise<T>&;

    template <typename T, ext::callable F0, ext::callable F1>
    auto react(ext::promise<T>& promise, v8::Local<v8::Context> realm, ext::optional<F0>&& fullfilled_steps = ext::nullopt, ext::optional<F1>&& rejected_steps = ext::nullopt) -> void;

    template <typename T, ext::callable F>
    auto upon_fulfillment(ext::promise<T>& promise, v8::Local<v8::Context> realm, F&& steps) -> ext::promise<T>&;

    template <typename T, ext::callable F>
    auto upon_rejection(ext::promise<T>& promise, v8::Local<v8::Context> realm, F&& steps) -> ext::promise<T>&;

    template <typename T, ext::callable F>
    auto upon_settlement(ext::promise<T>& promise, v8::Local<v8::Context> realm, F&& steps) -> ext::promise<T>&;

    template <typename T, ext::callable F0, ext::callable F1>
    auto wait_for_all(ext::vector_span<ext::promise<T>*> promises, v8::Local<v8::Context> realm, F0&& success_steps, F1&& failure_steps) -> void;

    template <typename T>
    auto get_promise_for_waiting_for_all(ext::vector_span<ext::promise<T>*> promises, v8::Local<v8::Context> realm) -> ext::promise<T>;

    template <typename T>
    auto mark_as_handled(ext::promise<T>& promise) -> void;

    // Not in spec
    template <typename T>
    auto wait_for_promise_to_fulfill_or_reject(ext::promise<T>&, v8::Local<v8::Context> realm) -> void;

    template <typename T>
    auto has_fulfilled(ext::promise<T>& promise, v8::Local<v8::Context> realm) -> ext::tuple<ext::boolean, ext::optional<T>>;

    template <typename E, typename T>
    auto has_rejected(ext::promise<T>& promise, v8::Local<v8::Context> realm) -> ext::tuple<ext::boolean, ext::optional<E>>;

    /* 3.2.25 */
    template <typename T>
    auto create_array_buffer(T&& byte_sequence, v8::Local<v8::Context> realm) -> ext::array_buffer;

    template <typename U, typename T>
    auto create_array_buffer_view(T&& byte_sequence, v8::Local<v8::Context> realm) -> U;

    auto get_copy_of_bytes_in_buffer_source(ext::buffer_source& source, v8::Local<v8::Context> realm) -> void*;

    auto byte_length(ext::buffer_source& source, v8::Local<v8::Context> realm) -> ext::number<size_t>;

    auto underlying_data(ext::buffer_source& source, v8::Local<v8::Context> realm) -> ext::array_buffer;

    template <typename T>
    auto write(T&& byte_sequence, ext::array_buffer& array_buffer, v8::Local<v8::Context> realm) -> ext::array_buffer&;

    template <typename T>
    auto write(T&& byte_sequence, ext::array_buffer_view& array_buffer, v8::Local<v8::Context> realm) -> ext::array_buffer_view&;

    auto detach_array_buffer(ext::array_buffer& array_buffer, v8::Local<v8::Context> realm) -> void;

    auto is_detached(ext::array_buffer& array_buffer, v8::Local<v8::Context> realm) -> ext::boolean;

    auto transfer(ext::array_buffer& array_buffer, v8::Local<v8::Context> realm, v8::Local<v8::Context> target_realm);

    // TDODO : not in spec
    auto viewed_buffer(ext::array_buffer_view& array_buffer_view) -> ext::array_buffer&;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_IDL_DETAIL_TYPE_MAPPING_INTERNALS_HPP
