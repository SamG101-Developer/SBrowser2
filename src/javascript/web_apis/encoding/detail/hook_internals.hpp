#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_DETAIL_HOOK_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_DETAIL_HOOK_INTERNALS_HPP

#include "ext/expected.ixx"
#include "ext/keywords.ixx"
#include INCLUDE_INNER_TYPES(encoding)

namespace encoding::detail
{
    auto utf8_decode(
            io_queue_t& io_queue,
            io_queue_t&& output = {})
            -> io_queue_t;

    auto utf8_decode_without_bom(
            io_queue_t& io_queue,
            io_queue_t&& output = {})
            -> io_queue_t;

    auto utf8_decode_without_bom_or_fail(
            io_queue_t& io_queue,
            io_queue_t&& output = {})
            -> ext::expected<io_queue_t>;

    auto utf8_encode(
            io_queue_t& io_queue,
            io_queue_t&& output = {})
            -> io_queue_t;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_DETAIL_HOOK_INTERNALS_HPP
