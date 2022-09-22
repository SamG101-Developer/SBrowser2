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
    explicit text(ext::string&& new_data = "");

public js_methods:
    auto split_text(ext::number<ulong> offset) -> text;

public js_properties:
    ext::property<ext::string> whole_text;

public cpp_members:
    MAKE_PIMPL(text);
    MAKE_V8_AVAILABLE;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(node_type) override {return TEXT_NODE;}
    DEFINE_CUSTOM_GETTER(node_name) override {return "#text";};
    DEFINE_CUSTOM_GETTER(whole_text);
};


#endif //SBROWSER2_TEXT_HPP
