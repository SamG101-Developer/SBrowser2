module;
#include "ext/macros.hpp"


export module apis.encoding.mixins.text_encoder_common:p;
import apis.dom_object;


DEFINE_PRIVATE_CLASS(encoding::mixins, text_encoder_common)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(text_encoder_common);

public:
    ext::string encoding = u"utf-8";
};
