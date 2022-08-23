#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_MIXINS_TEXT_ENCODER_COMMON_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_MIXINS_TEXT_ENCODER_COMMON_HPP

#include "dom_object.hpp"
namespace encoding::mixins {class text_encoder_common;}


class encoding::mixins::text_encoder_common
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(text_encoder_common);
    text_encoder_common() = default;

public js_properties:
    ext::property<ext::string> encoding;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_MIXINS_TEXT_ENCODER_COMMON_HPP
