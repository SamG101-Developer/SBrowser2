#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_MIXINS_TEXT_DECODER_COMMON_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_MIXINS_TEXT_DECODER_COMMON_HPP


namespace encoding::mixins {class text_decoder_common;}
namespace encoding::mixins {class text_decoder_common_private;}


#include INCLUDE_INNER_TYPES(encoding)
namespace encoding {class encoding;}


class encoding::mixins::text_decoder_common
        : public virtual dom_object
{
public constructors:
    text_decoder_common();
    MAKE_PIMPL(text_decoder_common);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(encoding, ext::string);
    DEFINE_GETTER(fatal, ext::boolean);
    DEFINE_GETTER(ignore_bom, ext::boolean);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_MIXINS_TEXT_DECODER_COMMON_HPP
