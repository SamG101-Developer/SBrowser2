module;
#include "ext/macros/pimpl.hpp"


module apis.encoding.mixins.text_encoder_common;
import ext.core;


auto encoding::mixins::text_encoder_common::get_encoding() const -> ext::string_view
{
    return u"utf-8";
}
