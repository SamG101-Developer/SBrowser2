module;
#include "ext/macros/macros.hpp"
#include <swl/variant.hpp>


export module apis.encoding.mixins.text_decoder_common_private;
import apis.dom_object_private;

import apis.encoding.types;
import ext.core;


DEFINE_PRIVATE_CLASS(encoding::mixins, text_decoder_common)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(text_decoder_common);

public:
    std::unique_ptr<detail::encoding_t> encoding;
    std::unique_ptr<detail::decoder_t> decoder;

    detail::io_queue_t io_queue;
    ext::boolean ignore_bom;
    ext::boolean bom_seen;
    ext::variant<detail::decoder_error_mode_t, detail::encoder_error_mode_t> error_mode;
};
