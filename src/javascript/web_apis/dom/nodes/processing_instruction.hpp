#ifndef SBROWSER2_PROCESSING_INSTRUCTION_HPP
#define SBROWSER2_PROCESSING_INSTRUCTION_HPP

#include "dom/nodes/character_data.hpp"
#include "css/cssom/mixins/link_style.hpp"
namespace dom::nodes {class processing_instruction;}
namespace dom::nodes {class processing_instruction_private;}


class dom::nodes::processing_instruction final
        : public character_data
        , public css::cssom::mixins::link_style
{
public cpp_members:
    processing_instruction();
    MAKE_PIMPL(processing_instruction);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(node_type, ext::number<ushort>) override {return PROCESSING_INSTRUCTION_NODE;}

    /* CSSOM */
    DEFINE_GETTER(target, ext::string);
    DEFINE_SETTER(data, ext::string);
};


#endif //SBROWSER2_PROCESSING_INSTRUCTION_HPP
