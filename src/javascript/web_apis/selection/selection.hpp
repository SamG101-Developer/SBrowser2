#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SELECTION_SELECTION_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SELECTION_SELECTION_HPP

#include "dom_object.hpp"
namespace selection {class selection;}



#include "ext/type_traits.ixx"
namespace dom::nodes {class node;}
namespace dom::node_ranges {class range;}


class selection::selection
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(selection);
    selection() = default;

private js_properties:
    ext::property<std::unique_ptr<dom::nodes::node>> anchor_node;
    ext::property<std::unique_ptr<dom::nodes::node>> focus_node;
    ext::property<ext::number<ulong>> anchor_offset;
    ext::property<ext::number<ulong>> focus_offset;
    ext::property<ext::number<ulong>> range_count;
    ext::property<ext::boolean> is_collapsed;
    ext::property<ext::string> type;

public js_methods:
    auto get_range_at(ext::number<ulong> index) -> dom::node_ranges::range*;
    auto add_range(dom::node_ranges::range* range) -> void;

    auto remove_range(dom::node_ranges::range* range) -> void;
    auto remove_all_ranges() -> void;
    auto empty() -> void;

    auto collapse(dom::nodes::node* node, ext::number<ulong> offset = 0) -> void;
    auto collapse_to_start() -> void;
    auto collapse_to_end() -> void;

    auto set_position(dom::nodes::node* node, ext::number<ulong> offset = 0) -> void;

    auto extend(dom::nodes::node* node, ext::number<ulong> offset = 0) -> void;
    auto set_base_and_extend(dom::nodes::node* anchor_node, ext::number<ulong> anchor_offset, dom::nodes::node* focus_node, const ext::number<ulong> focus_offset) -> void;
    auto select_all_children(dom::nodes::node* node);

    auto modify(ext::string_view alter, ext::string_view direction = "", ext::string_view granularity = "") -> void;
    auto delete_from_document() -> void;
    auto contains_node(dom::nodes::node* node, ext::boolean allow_partial_containment = false) -> ext::boolean;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
    auto to_json() const -> ext::string override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SELECTION_SELECTION_HPP
