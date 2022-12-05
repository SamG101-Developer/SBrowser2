#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_TEXT_ENCODER_STREAM_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_TEXT_ENCODER_STREAM_HPP

// Inheritance Includes & This Class

#include "encoding/mixins/text_encoder_common.hpp"
#include "streams/mixins/generic_transform_stream.hpp"
namespace encoding {class text_encoder_stream;}
namespace encoding {class text_encoder_stream_private;}

// Other Includes & Forward Declarations


class encoding::text_encoder_stream
        : virtual public dom_object
        , public encoding::mixins::text_encoder_common
        , public streams::mixins::generic_transform_stream
{
public constructors:
    text_encoder_stream();
    MAKE_PIMPL(text_encoder_stream);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_TEXT_ENCODER_STREAM_HPP
