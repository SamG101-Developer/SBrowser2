#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_TEXT_DECODER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_TEXT_DECODER_HPP


#include "encoding/mixins/text_decoder_common.hpp"
namespace encoding {class text_decoder;}
namespace encoding {class text_decoder_private;}

#include INCLUDE_INNER_TYPES(encoding)
#include INCLUDE_INNER_TYPES(web_idl)


class encoding::text_decoder
        : public virtual dom_object
        , public mixins::text_decoder_common
{
public constructors:
    text_decoder(ext::string_view label = u8"utf-8", detail::text_decoder_options_t&& options = {});
    MAKE_PIMPL(text_decoder);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto decode(v8::Local<v8::BufferSource> input, detail::text_decode_options_t&& options = {});
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_TEXT_DECODER_HPP
