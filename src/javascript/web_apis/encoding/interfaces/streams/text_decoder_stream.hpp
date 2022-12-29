#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_TEXT_DECODER_STREAM_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_TEXT_DECODER_STREAM_HPP

// Inheritance Includes & This Class

#include "encoding/mixins/text_decoder_common.hpp"
#include "streams/mixins/generic_transform_stream.hpp"
namespace encoding {class text_decoder_stream;}
namespace encoding {class text_decoder_stream_private;}

// Other Includes & Forward Declarations
#include INCLUDE_INNER_TYPES(encoding)


class encoding::text_decoder_stream
        : virtual public dom_object
        , public encoding::mixins::text_decoder_common
        , public streams::mixins::generic_transform_stream
{
public constructors:
    text_decoder_stream(ext::string&& label = u"utf-8", detail::text_decoder_options_t&& options = {});
    MAKE_PIMPL(text_decoder_stream);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_TEXT_DECODER_STREAM_HPP
