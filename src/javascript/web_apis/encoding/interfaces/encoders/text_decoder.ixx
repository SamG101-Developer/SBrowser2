module;
#include "ext/macros.hpp"


export module apis.encoding.text_decoder;
import apis.dom_object;
import apis.encoding.mixins.text_decoder_common;


DEFINE_PUBLIC_CLASS(encoding, text_decoder) final
        : public virtual dom_object
        , public encoding::text_decoder_common
{
public typedefs:
    using text_decoder_options_t = ext::map<ext::string, ext::any>;
    using text_decode_options_t = ext::map<ext::string, ext::any>;

public constructors:
    text_decoder(ext::string_view label = u8"utf-8", text_decoder_options_t&& options = {});
    MAKE_PIMPL(text_decoder);
    MAKE_V8_AVAILABLE(ALL);

private js_methods:
    auto decode(ext::buffer_source&& input, text_decode_options_t&& options = {});
};
