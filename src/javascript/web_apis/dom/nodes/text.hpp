#ifndef SBROWSER2_TEXT_HPP
#define SBROWSER2_TEXT_HPP

#include <web_apis/dom/nodes/character_data.hpp>
#include <web_apis/dom/mixins/slottable.hpp>
namespace dom::nodes {class text;}


class dom::nodes::text
        : public character_data
        , public mixins::slottable
{
public constructors:
    text();
    explicit text(ext::string_view new_data);

public js_methods:
    auto split_text(ext::number_view<ulong> offset) -> text*;

public js_properties:
    ext::property<ext::string> whole_text;

public cpp_methods:
    [[nodiscard]] auto to_qt() const -> QLabel* override {return qobject_cast<QLabel*>(m_rendered_widget);};
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_accessors:
    auto get_node_name() const -> ext::string override {return "#text";};
    auto get_whole_text() const -> ext::string;
};


#endif //SBROWSER2_TEXT_HPP
