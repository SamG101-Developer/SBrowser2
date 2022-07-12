#ifndef SBROWSER2_COMMENT_HPP
#define SBROWSER2_COMMENT_HPP

#include "dom/nodes/character_data.hpp"
namespace dom::nodes {class comment;}


class dom::nodes::comment final
        : public character_data
{
public constructors:
    comment();
    comment(ext::string_view new_data);

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

private cpp_accessors:
    [[nodiscard]] auto get_node_type() const -> ext::number<ushort> override {return COMMENT_NODE;}
    [[nodiscard]] auto get_node_name() const -> ext::string override;
};


#endif //SBROWSER2_COMMENT_HPP
