module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.encoding.mixins.text_decoder_common;
import apis.dom_object;

import ext.core;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(encoding::mixins, text_decoder_common)
        : public virtual dom_object
{
public constructors:
    text_decoder_common();
    MAKE_PIMPL(text_decoder_common);
    MAKE_V8_AVAILABLE(MIXIN);

private js_properties:
    DEFINE_GETTER(encoding, ext::string);
    DEFINE_GETTER(fatal, ext::boolean);
    DEFINE_GETTER(ignore_bom, ext::boolean);
};
