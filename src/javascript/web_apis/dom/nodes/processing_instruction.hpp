#ifndef SBROWSER2_PROCESSING_INSTRUCTION_HPP
#define SBROWSER2_PROCESSING_INSTRUCTION_HPP

#include <web_apis/dom/nodes/character_data.hpp>
namespace dom::nodes {class processing_instruction;}


class dom::nodes::processing_instruction final
        : public character_data
{
public cpp_properties:
    ext::property<ext::string> target;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
};


#endif //SBROWSER2_PROCESSING_INSTRUCTION_HPP
