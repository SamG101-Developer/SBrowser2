#ifndef SBROWSER2_CHARACTER_DATA_HPP
#define SBROWSER2_CHARACTER_DATA_HPP

#include <web_apis/dom/nodes/node.hpp>
#include <web_apis/dom/mixins/child_node.hpp>
#include <web_apis/dom/mixins/non_document_type_child_node.hpp>
namespace dom::nodes {class character_data;}

#include <QtWidgets/QLabel>


class dom::nodes::character_data
        : public node
        , public mixins::child_node
        , public mixins::non_document_type_child_node
{
public constructors:
    character_data();

public js_methods:
    [[nodiscard]] auto substring_data(ext::number_view<ulong> offset, ext::number_view<ulong> count) const -> ext::string;
    auto append_data(ext::string_view new_data) -> void;
    auto insert_data(ext::number_view<ulong> offset, ext::string_view new_data) -> void;
    auto delete_data(ext::number_view<ulong> offset, ext::number_view<ulong> count) -> void;
    auto replace_data(ext::number_view<ulong> offset, ext::number_view<ulong> count, ext::string_view new_data) -> void;

public js_properties:
    ext::property<ext::string> data;
    ext::property<ext::number<ulong>> length;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

private cpp_accessors:
    [[nodiscard]] auto get_node_name() const -> ext::string override {return "";};
    [[nodiscard]] auto get_node_value() const -> ext::string override {return data();};
    [[nodiscard]] auto get_text_content() const -> ext::string override {return data();};
    [[nodiscard]] auto get_length() const -> ext::number<ulong> {return data->length();};

    auto set_node_value(ext::string_view val) -> void override {replace_data(0, length(), val);};
    auto set_text_content(ext::string_view val) -> void override {replace_data(0, length(), val);};
};


#endif //SBROWSER2_CHARACTER_DATA_HPP
