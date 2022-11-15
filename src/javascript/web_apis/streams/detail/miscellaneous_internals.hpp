#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_DETAIL_MISCELLANEOUS_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_DETAIL_MISCELLANEOUS_INTERNALS_HPP

#include <v8-forward.h>
#include "ext/boolean.hpp"
#include "ext/number.hpp"


namespace streams::detail
{
    auto can_transfer_array_buffer(
            v8::Local<v8::ArrayBuffer> O)
            -> ext::boolean;

    auto transfer_array_buffer(
            v8::Local<v8::ArrayBuffer> O)
            -> v8::Local<v8::ArrayBuffer>;

    auto cast_as_uint8array(
            v8::Local<v8::Object> O)
            -> v8::Local<v8::Uint8Array>;

    template <typename T>
    auto is_non_negative_number(
            ext::number<T> number)
            -> ext::boolean;

    auto structured_clone(
            v8::Local<v8::Object>)
            -> v8::Local<v8::String>; // TODO : or ext::string?
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_DETAIL_MISCELLANEOUS_INTERNALS_HPP
