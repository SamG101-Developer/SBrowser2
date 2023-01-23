module;
#include "ext/macros.hpp"


export module apis.encoding.text_encoder_stream:p;
import apis.dom_object;
import apis.encoding.mixins.text_encoder_common;
import apis.streams.mixins.generic_transform_stream;


DEFINE_PRIVATE_CLASS(encoding, text_encoder_stream)
        : virtual dom_object_private
        , encoding::mixins::text_encoder_common_private
        , streams::mixins::generic_transform_stream_private
{
public:
    MAKE_QIMPL(text_encoder_stream);
};
