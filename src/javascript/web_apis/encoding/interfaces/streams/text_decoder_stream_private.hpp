#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_TEXT_DECODER_STREAM_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_TEXT_DECODER_STREAM_PRIVATE_HPP

#include "ext/pimpl.ixx"

#include "encoding/mixins/text_decoder_common_private.hpp"
#include "streams/mixins/generic_transform_stream_private.hpp"


DEFINE_PRIVATE_CLASS(encoding, text_decoder_stream)
        : virtual dom_object_private
        , encoding::mixins::text_decoder_common_private
        , streams::mixins::generic_transform_stream_private
{
    MAKE_QIMPL(text_decoder_stream);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_TEXT_DECODER_STREAM_PRIVATE_HPP
