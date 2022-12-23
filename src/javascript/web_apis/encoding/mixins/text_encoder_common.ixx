module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.encoding.mixins.text_encoder_common;
import apis.dom_object;

import ext.core;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(encoding, text_encoder_common) final
        : public virtual dom_object
{
public constructors:
    text_encoder_common();
    MAKE_PIMPL(text_encoder_common);
    MAKE_V8_AVAILABLE(ALL);

private js_properties:
    DEFINE_GETTER(encoding, ext::string_view);
};
