#ifndef SBROWSER2_CHARACTER_DATA_HPP
#define SBROWSER2_CHARACTER_DATA_HPP

#include "dom/nodes/node.hpp"
#include "dom/mixins/child_node.hpp"
#include "dom/mixins/non_document_type_child_node.hpp"
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
    [[nodiscard]] auto substring_data(const ext::number<ulong>& offset, const ext::number<ulong>& count) const -> ext::string;
    auto append_data(ext::string&& new_data) -> void;
    auto insert_data(const ext::number<ulong>& offset, ext::string&& new_data) -> void;
    auto delete_data(const ext::number<ulong>& offset, const ext::number<ulong>& count) -> void;
    auto replace_data(const ext::number<ulong>& offset, const ext::number<ulong>& count, ext::string&& new_data) -> void;

public js_properties:
    ext::property<ext::string> data;
    ext::property<ext::number<ulong>> length;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

private cpp_accessors:
    DEFINE_GETTER(node_name) override {return "";};
    DEFINE_GETTER(node_value) override {return data();};
    DEFINE_GETTER(text_content) override {return data();};
    DEFINE_GETTER(length) {return data().length();};

    DEFINE_SETTER(node_value) override {replace_data(0, length(), std::move(val));};
    DEFINE_SETTER(text_content) override {replace_data(0, length(), std::move(val));};
};


#endif //SBROWSER2_CHARACTER_DATA_HPP
