#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_TEXT_ENCODER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_TEXT_ENCODER_HPP

#include "dom_object.hpp"
#include "encoding/mixins/text_encoder_common.hpp"
namespace encoding {class text_encoder;}
namespace encoding {class text_encoder_private;}

#include <v8-forward.h>
#include INCLUDE_INNER_TYPES(encoding)


class encoding::text_encoder
        : public virtual dom_object
        , public mixins::text_encoder_common
{
public constructors:
    text_encoder();
    MAKE_PIMPL(text_encoder);
    MAKE_V8_AVAILABLE;

private js_methods:
    auto encode(ext::string&& input = u8"") -> v8::Uint8Array;
    auto encode_into(ext::string&& source, v8::Local<v8::Uint8Array> destination) -> detail::text_encoder_encoder_into_result_t;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_TEXT_ENCODER_HPP
