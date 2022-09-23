#ifndef SBROWSER2_CHARACTER_DATA_HPP
#define SBROWSER2_CHARACTER_DATA_HPP

#include "dom/nodes/node.hpp"
#include "dom/mixins/child_node.hpp"
#include "dom/mixins/non_document_type_child_node.hpp"
namespace dom::nodes {class character_data;}

#include "dom/nodes/character_data_private.hpp"


class dom::nodes::character_data
        : public node
        , public mixins::child_node
        , public mixins::non_document_type_child_node
{
public constructors:
    character_data();
    MAKE_PIMPL(character_data);
    MAKE_V8_AVAILABLE;

public js_methods:
    [[nodiscard]] auto substring_data(ext::number<ulong> offset, ext::number<ulong> count) const -> ext::string;
    auto append_data(ext::string&& new_data) -> ext::string;
    auto insert_data(ext::number<ulong> offset, ext::string&& new_data) -> ext::string;
    auto delete_data(ext::number<ulong> offset, ext::number<ulong> count) -> ext::string;
    auto replace_data(ext::number<ulong> offset, ext::number<ulong> count, ext::string&& new_data) -> ext::string;

private cpp_accessors:
    DEFINE_GETTER(node_name, ext::string) override {return "";};
    DEFINE_GETTER(node_value, ext::string) override {return d_ptr->data;};
    DEFINE_GETTER(text_content, ext::string) override {return d_ptr->data;};

    DEFINE_SETTER(node_value, ext::string) override {return replace_data(0, d_ptr->data.length(), std::move(new_node_value));};
    DEFINE_SETTER(text_content, ext::string) override {return replace_data(0, d_ptr->data.length(), std::move(new_text_content));};


    DEFINE_GETTER(data, ext::string) {return d_ptr->data;}
    DEFINE_GETTER(length, ext::number<ulong>) {return d_ptr->data.length();};

    DEFINE_SETTER(data, ext::string) {return d_ptr->data = std::move(new_data);}
};


#endif //SBROWSER2_CHARACTER_DATA_HPP
