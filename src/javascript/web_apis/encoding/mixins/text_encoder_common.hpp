#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_MIXINS_TEXT_ENCODER_COMMON_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_MIXINS_TEXT_ENCODER_COMMON_HPP


namespace encoding::mixins {class text_encoder_common;}
namespace encoding::mixins {class text_encoder_common_private;}


class encoding::mixins::text_encoder_common
        : public virtual dom_object
{
public constructors:
    text_encoder_common();
    MAKE_PIMPL(text_encoder_common);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(encoding, ext::string_view);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_MIXINS_TEXT_ENCODER_COMMON_HPP
