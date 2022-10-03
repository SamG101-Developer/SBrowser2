#ifndef SBROWSER2_TEXT_HPP
#define SBROWSER2_TEXT_HPP

#include "dom/nodes/character_data.hpp"
#include "dom/mixins/slottable.hpp"
namespace dom::nodes {class text;}

#include "dom/nodes/text_private.hpp"


class dom::nodes::text
        : public character_data
        , public mixins::slottable
{
public constructors:
    text(ext::string&& new_data = "");
    MAKE_PIMPL(text);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto split_text(ext::number<ulong> offset) -> std::unique_ptr<text>;

private js_properties:
    DEFINE_GETTER(node_type, ext::number<ushort>) override {return TEXT_NODE;}
    DEFINE_GETTER(node_name, ext::string);
    DEFINE_GETTER(whole_text, ext::string);
};


#endif //SBROWSER2_TEXT_HPP
