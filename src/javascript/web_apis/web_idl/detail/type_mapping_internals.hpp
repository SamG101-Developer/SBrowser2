#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_IDL_DETAIL_TYPE_MAPPING_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_IDL_DETAIL_TYPE_MAPPING_INTERNALS_HPP

#include "ext/any.hpp"
#include "ext/map.hpp"
#include "ext/optional.hpp"
#include "ext/promise.hpp"
#include "ext/span.hpp"
#include "ext/symbol.hpp"
#include "ext/type_traits.hpp"
#include <v8-forward.h>
class dom_object;


namespace web_idl::detail
{
    template <typename T>
    auto convert(v8::Isolate* isolate, v8::Local<v8::Value> V) -> T;

    template <> /* 3.2.1 - Any */
    auto convert<ext::any>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::any;

    template <> /* 3.2.2 - Undefined (v8::Undefined -> void; v8::Null -> nullptr)*/
    auto convert<void>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> void;

    template <> /* 3.2.3 - Boolean */
    auto convert<ext::boolean>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::boolean;

    template <> /* 3.2.4.1 - Byte */
    auto convert<ext::number<int8_t>>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::number<int8_t>;

    template <> /* 3.2.4.2 - Octet */
    auto convert<ext::number<uint8_t>>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::number<uint8_t>;

    template <> /* 3.2.4.3 - Short */
    auto convert<ext::number<int16_t>>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::number<int16_t>;

    template <> /* 3.2.4.4 - Unsigned short */
    auto convert<ext::number<uint16_t>>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::number<uint16_t>;

    template <> /* 3.2.4.5 - Long */
    auto convert<ext::number<int32_t>>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::number<int32_t>;

    template <> /* 3.2.4.6 - Unsigned long */
    auto convert<ext::number<uint32_t>>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::number<uint32_t>;

    template <> /* 3.2.4.7 - Long long */
    auto convert<ext::number<int64_t>>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::number<int64_t>;

    template <> /* 3.2.4.8 - Unsigned long long */
    auto convert<ext::number<uint64_t>>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::number<uint64_t>;

    template <> /* 3.2.5 - Float */
    auto convert<ext::number<float>>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::number<float>;

    template <> /* 3.2.6 - Unrestricted float */
    auto convert<ext::number<float, true>>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::number<float, true>;

    template <> /* 3.2.7 - Double */
    auto convert<ext::number<double>>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::number<double>;

    template <> /* 3.2.8 - Unrestricted double */
    auto convert<ext::number<double, true>>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::number<double, true>;

    template <> /* 3.2.9 - BigInt */
    auto convert<ext::number<bigint>>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::number<bigint>;

    template <> /* 3.2.10 / 3.2.11 / 3.2.12 - String */
    auto convert<ext::string>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::string;

    template <> /* 3.2.13 - Object TODO : void*? */
    auto convert<dom_object*>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> dom_object*;

    template <> /* 3.2.14 - Symbol */
    auto convert<ext::symbol*>(v8::Isolate* isolate, v8::Local<v8::Value> V) -> ext::symbol*;

    // template <> /* 3.2.15 - Interface TODO */
    // template <> /* 3.2.16 - Callback Interface TODO */
    // template <> /* 3.2.17 - Dictionary TODO (ext::map<K, V>) */
    // template <> /* 3.2.18 - Enums TODO */
    // template <> /* 3.2.19 - Callback TODO (ext::function<Ts...>)? */
    // template <> /* 3.2.20 - Nullable TODO (ext::optional<T>)? */
    // template <> /* 3.2.21 - Sequence TODO (ext::vector<T>) */
    // template <> /* 3.2.22 - Record TODO (const ext::map<K, V>)? */
    // template <> /* 3.2.23 - Enums TODO (ext::promise<T>) */
    // template <> /* 3.2.24 - Union TODO (ext::variant<Ts...>) */
    // template <> /* 3.2.25 - ArrayBuffer TODO required? been using v8::ArrayBuffer in code anyway */

    /* 3.2.23.1 */
    template <typename T>
    auto create_promise(v8::Local<v8::Context> realm) -> ext::promise<T>;

    template <typename T>
    auto create_resolved_promise(T&& x, v8::Local<v8::Context> realm) -> ext::promise<T>;

    template <typename T>
    auto create_rejected_promise(T&& reason, v8::Local<v8::Context> realm) -> ext::promise<T>;

    template <typename T>
    auto resolve_promise(ext::promise<T>& promise, v8::Local<v8::Context> realm, ext::optional<T>&& x = ext::nullopt) -> void;

    template <typename T, typename U>
    auto reject_promise(ext::promise<T>& promise, v8::Local<v8::Context> realm, U&& reason) -> void;

    template <typename T, ext::callable F0, ext::callable F1>
    auto react(ext::promise<T>& promise, v8::Local<v8::Context> realm, ext::optional<F0>&& fullfilled_steps = ext::nullopt, ext::optional<F1>&& rejected_steps = ext::nullopt) -> void;

    template <typename T, ext::callable F>
    auto upon_fulfillment(ext::promise<T>& promise, v8::Local<v8::Context> realm, T&& v) -> void;

    template <typename T, typename U, typename F>
    auto upon_rejection(ext::promise<T>& promise, v8::Local<v8::Context> realm, U&& r) -> void;

    template <typename T, ext::callable F0, ext::callable F1>
    auto wait_for_all(ext::vector_span<ext::promise<T>*> promises, v8::Local<v8::Context> realm, F0&& success_steps, F1&& failure_steps) -> void;

    template <typename T>
    auto get_promise_for_waiting_for_all(ext::vector_span<ext::promise<T>*> promises, v8::Local<v8::Context> realm) -> ext::promise<T>;

    template <typename T>
    auto mark_as_handled(ext::promise<T>& promise) -> void;

    /* 3.2.25 */
    template <typename T>
    auto create_array_buffer(T byte_sequence, v8::Local<v8::Context> realm); // TODO -> ?

    template <typename T>
    auto create_array_buffer_view(T byte_sequence, v8::Local<v8::Context> realm); // TODO -> ?

    auto get_copy_of_bytes_in_buffer_source(/* TODO */); // TODO : -> TODO
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_IDL_DETAIL_TYPE_MAPPING_INTERNALS_HPP
