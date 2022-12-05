#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_TEXT_ENCODER_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_TEXT_ENCODER_PRIVATE_HPP

#include "ext/pimpl.ixx"

#include "encoding/mixins/text_encoder_common_private.hpp"


DEFINE_PRIVATE_CLASS(encoding, text_encoder_private)
        : virtual dom_object_private
        , encoding::mixins::text_encoder_common_private
{
    MAKE_QIMPL(text_encoder_private);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_TEXT_ENCODER_PRIVATE_HPP
