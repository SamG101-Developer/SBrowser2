module;
#include "ext/macros.hpp"


export module apis.encoding.text_encoder_stream;
import apis.dom_object;
import apis.encoding.mixins.text_encoder_common;
import apis.streams.mixins.generic_transform_stream;


class encoding::text_encoder_stream
        : virtual public dom_object
        , public encoding::mixins::text_encoder_common
        , public streams::mixins::generic_transform_stream
{
public constructors:
    text_encoder_stream();
    MAKE_PIMPL(text_encoder_stream);
    MAKE_V8_AVAILABLE(ALL);
};
