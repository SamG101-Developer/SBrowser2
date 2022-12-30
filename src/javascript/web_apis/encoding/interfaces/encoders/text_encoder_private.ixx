module;
#include "ext/macros.hpp"


export module apis.encoding.text_encoder:p;
import apis.dom_object;
import apis.encoding.mixins.text_encoder_common;


DEFINE_PRIVATE_CLASS(encoding, text_encoder_private)
        : virtual dom_object_private
        , encoding::text_encoder_common_private
{
public:
    MAKE_QIMPL(text_encoder_private);
};
