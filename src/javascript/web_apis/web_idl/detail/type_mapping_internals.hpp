#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_IDL_DETAIL_TYPE_MAPPING_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_IDL_DETAIL_TYPE_MAPPING_INTERNALS_HPP

#include "ext/any.hpp"
#include "ext/map.hpp"
#include "ext/optional.hpp"
#include "ext/promise.hpp"
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

    /* 3.2.23.1 */
    template <typename T>
    auto create_promise(v8::Local<v8::Context> realm) -> ext::promise<T>;

    template <typename T>
    auto create_resolved_promise(T&& x, v8::Local<v8::Context> realm) -> ext::promise<T>;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_IDL_DETAIL_TYPE_MAPPING_INTERNALS_HPP
