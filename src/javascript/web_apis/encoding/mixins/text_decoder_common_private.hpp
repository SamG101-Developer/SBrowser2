#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_MIXINS_TEXT_DECODER_COMMON_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_MIXINS_TEXT_DECODER_COMMON_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom_object_private.hpp"

#include INCLUDE_INNER_TYPES(encoding)
#include "ext/variant.ixx"


DEFINE_PRIVATE_CLASS(encoding::mixins, text_decoder_common)
        : virtual dom_object_private
{
    MAKE_QIMPL(text_decoder_common);
    std::unique_ptr<detail::encoding_t> encoding;
    std::unique_ptr<detail::decoder_t> decoder;

    detail::io_queue_t io_queue;
    ext::boolean ignore_bom;
    ext::boolean bom_seen;
    ext::variant<detail::decoder_error_mode_t, detail::encoder_error_mode_t> error_mode;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_MIXINS_TEXT_DECODER_COMMON_PRIVATE_HPP
