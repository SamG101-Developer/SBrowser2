module;
#include "ext/macros/macros.hpp"


export module apis.encoding.text_decoder_private;
import apis.dom_object_private;
import apis.encoding.mixins.text_decoder_common_private;

import ext.core;


DEFINE_PRIVATE_CLASS(encoding, text_decoder)
        : virtual dom_object_private
        , mixins::text_decoder_common_private
{
public:
    MAKE_QIMPL(text_decoder);

public:
    ext::boolean do_not_flush;
};
