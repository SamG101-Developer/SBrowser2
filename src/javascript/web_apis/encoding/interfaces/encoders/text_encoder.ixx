module;
#include "ext/macros.hpp"


export module apis.encoding.text_encoder;
import apis.dom_object;
import apis.encoding.mixins.text_encoder_common;


DEFINE_PUBLIC_CLASS(encoding, text_encoder) final
        : public virtual dom_object
        , public encoding::text_encoder_common
{
public typedefs:
    using text_encoder_encoder_into_result_t = ext::map<ext::string, ext::any>;

public constructors:
    text_encoder();
    MAKE_PIMPL(text_encoder);
    MAKE_V8_AVAILABLE(ALL);

private js_methods:
    auto encode(ext::string&& input = u8"") -> ext::uint8_array;
    auto encode_into(ext::string&& source, ext::uint8_array& destination) -> text_encoder_encoder_into_result_t;
};
