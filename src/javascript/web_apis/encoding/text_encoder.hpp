#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_TEXT_ENCODER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_TEXT_ENCODER_HPP

#include "dom_object.hpp"
#include "encoding/mixins/text_encoder_common.hpp"
namespace encoding {class text_encoder;}

#include <v8-forward.h>
#include USE_INNER_TYPES(encoding)


class encoding::text_encoder
        : public virtual dom_object
        , public mixins::text_encoder_common
{
public constructors:
    DOM_CTORS(text_encoder);
    text_encoder() = default;

public js_properties:
    auto encode(ext::string&& input = "") -> v8::Uint8Array;
    auto encode_into(ext::string&& source, v8::Local<v8::Uint8Array> destination) -> detail::text_encoder_encoder_into_result_t;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_TEXT_ENCODER_HPP
