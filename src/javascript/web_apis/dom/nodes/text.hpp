#ifndef SBROWSER2_TEXT_HPP
#define SBROWSER2_TEXT_HPP

#include "dom/nodes/character_data.hpp"
#include "dom/mixins/slottable.hpp"
namespace dom::nodes {class text;}


class dom::nodes::text
        : public character_data
        , public mixins::slottable
{
public constructors:
    explicit text(ext::string&& new_data = "");

public js_methods:
    auto split_text(const ext::number<ulong>& offset) -> text;

public js_properties:
    ext::property<ext::string> whole_text;

public cpp_methods:
    [[nodiscard]] auto to_qt() const -> QLabel* override {return qobject_cast<QLabel*>(m_rendered_widget);};
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

private cpp_accessors:
    [[nodiscard]] auto get_node_type() const -> ext::number<ushort> override {return TEXT_NODE;}
    [[nodiscard]] auto get_node_name() const -> ext::string override {return "#text";};
    [[nodiscard]] auto get_whole_text() const -> ext::string;
};


#endif //SBROWSER2_TEXT_HPP
