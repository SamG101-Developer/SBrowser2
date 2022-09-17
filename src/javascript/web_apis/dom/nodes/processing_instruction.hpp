#ifndef SBROWSER2_PROCESSING_INSTRUCTION_HPP
#define SBROWSER2_PROCESSING_INSTRUCTION_HPP

#include "dom/nodes/character_data.hpp"
#include "css/cssom/mixins/link_style.hpp"
namespace dom::nodes {class processing_instruction;}


class dom::nodes::processing_instruction final
        : public character_data
        , public css::cssom::mixins::link_style
{
public cpp_properties:
    ext::property<ext::string> target;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(node_type) override {return PROCESSING_INSTRUCTION_NODE;}

    /* CSSOM */
    DEFINE_CUSTOM_SETTER(data);
};


#endif //SBROWSER2_PROCESSING_INSTRUCTION_HPP
