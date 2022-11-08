#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_MIXINS_TEXT_ENCODER_COMMON_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_MIXINS_TEXT_ENCODER_COMMON_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"

#include "ext/string.hpp"


DEFINE_PRIVATE_CLASS(encoding::mixins, text_encoder_common) : virtual dom_object_private
{
    ext::string encoding = u8"utf-8";
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_MIXINS_TEXT_ENCODER_COMMON_PRIVATE_HPP