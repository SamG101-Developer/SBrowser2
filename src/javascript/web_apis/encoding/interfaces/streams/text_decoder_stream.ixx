module;
#include "ext/macros.hpp"


export module text_decoder_stream;
import apis.dom_object;
import apis.encoding.mixins.text_decoder_common;
import apis.streams.mixins.generic_transform_stream;


DEFINE_PUBLIC_CLASS(encoding, text_decoder_stream) final
        : virtual public dom_object
        , public encoding::mixins::text_decoder_common
        , public streams::mixins::generic_transform_stream
{
public constructors:
    text_decoder_stream(ext::string&& label = u"utf-8", detail::text_decoder_options_t&& options = {});
    MAKE_PIMPL(text_decoder_stream);
    MAKE_V8_AVAILABLE(ALL);
};
