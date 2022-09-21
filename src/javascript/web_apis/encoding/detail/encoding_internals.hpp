#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_DETAIL_ENCODING_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_DETAIL_ENCODING_INTERNALS_HPP

#include "ext/map.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"
#include INCLUDE_INNER_TYPES(encoding)

namespace encoding {class encoding;}
namespace encoding::mixins {class text_decoder_common;}

namespace encoding::detail
{
    auto process_queue(
            encoder_decoder_t& encoder_decoder,
            io_queue_t& input,
            io_queue_t& output,
            ext::variant<encoder_error_mode_t, decoder_error_mode_t> mode)
            -> handle_state_t;

    auto process_item(
            item_t item,
            encoder_decoder_t& encoder_decoder,
            io_queue_t& input,
            io_queue_t& output,
            ext::variant<encoder_error_mode_t, decoder_error_mode_t> mode)
            -> handle_state_t;

    auto get_encoding(
            ext::string_view label)
            -> encoding;

    auto get_output_encoding(
            encoding* input_encoding)
            -> encoding;

    auto serialize_io_queue(
            mixins::text_decoder_common* decoder,
            io_queue_t& io_queue)
            -> ext::string;
};


struct encoding::detail::encoding_t
{
    ext::string name;
    ext::vector<ext::string> labels;
    ext::map<char, char> mapping;
};


struct encoding::detail::encoder_decoder_t
{
    handler_algorithm_t handler_algorithm;
};


struct encoding::detail::encoder_t : public encoder_decoder_t {};

struct encoding::detail::decoder_t : public encoder_decoder_t {};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_DETAIL_ENCODING_INTERNALS_HPP
