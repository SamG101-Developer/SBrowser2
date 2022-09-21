#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_TEXT_DECODER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_TEXT_DECODER_HPP

#include "dom_object.hpp"
#include "encoding/mixins/text_decoder_common.hpp"
namespace encoding::detail {class text_decoder;}

#include <v8-forward.h>
#include INCLUDE_INNER_TYPES(encoding)


class encoding::detail::text_decoder
        : public virtual dom_object
        , public mixins::text_decoder_common
{
public constructors:
    DOM_CTORS(text_decoder);
    text_decoder() = default;
    text_decoder(ext::string_view lavel = "utf-8", detail::text_decoder_options_t&& options = {});

public js_methods:
    auto decode(v8::Local<v8::ArrayBuffer> input, text_decode_options_t&& options = {});
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_TEXT_DECODER_HPP
