module;
#include "ext/macros/pimpl.hpp"


export module apis.encoding.text_encoder_private;
import apis.dom_object_private;
import apis.encoding.mixins.text_encoder_common_private;


DEFINE_PRIVATE_CLASS(encoding, text_encoder_private)
        : virtual dom_object_private
        , encoding::text_encoder_common_private
{
public:
    MAKE_QIMPL(text_encoder_private);
};
