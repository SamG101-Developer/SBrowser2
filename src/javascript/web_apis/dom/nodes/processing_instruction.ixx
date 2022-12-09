module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/constructors.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.dom.processing_instruction;
import apis.dom.character_data;
import apis.css.cssom.mixins.link_style;


DEFINE_PUBLIC_CLASS(dom, processing_instruction) final
        : public dom::character_data
        , public css::cssom::link_style
{
public constructors:
    processing_instruction();
    DOM_CTORS(processing_instruction);
    MAKE_PIMPL(processing_instruction);
    MAKE_V8_AVAILABLE(WINDOW);

private js_properties:
    DEFINE_GETTER(node_type, ext::number<ushort>) override {return PROCESSING_INSTRUCTION_NODE;}

    /* CSSOM */
    DEFINE_GETTER(target, ext::string_view);
    DEFINE_SETTER(data, ext::string);
};
