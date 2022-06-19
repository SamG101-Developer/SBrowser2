#ifndef SBROWSER2_RANGE_HPP
#define SBROWSER2_RANGE_HPP

#include <web_apis/dom/ranges/abstract_range.hpp>
namespace dom::node_ranges {class range;}

namespace dom::nodes {class document_fragment;}


class dom::node_ranges::range
        : public abstract_range
{
public constructors:
    using abstract_range::abstract_range;
    range();

public js_static_constants:
    static const short START_TO_START = 0;
    static const short START_TO_END = 1;
    static const short END_TO_END = 2;
    static const short END_TO_START = 3;

public js_methods:
    auto set_start(nodes::node* node, ext::number_view<ulong> offset) -> void;
    auto set_start_before(nodes::node* node) -> void;
    auto set_start_after(nodes::node* node) -> void;

    auto set_end(nodes::node* node, ext::number_view<ulong> offset) -> void;
    auto set_end_before(nodes::node* node) -> void;
    auto set_end_after(nodes::node* node) -> void;

    auto insert_node(nodes::node* node) -> void;
    auto intersects_node(const nodes::node* node) const -> bool;
    auto select_node(nodes::node* node) -> void;
    auto select_node_contents(nodes::node* node) -> void;

    auto compare_boundary_points(ext::number_view<ushort> how, ranges::range* source_range) -> short;
    auto compare_point(nodes::node* node, ext::number_view<ulong> offset) const -> short;

    auto extract_contents() -> nodes::document_fragment;
    auto clone_contents() -> nodes::document_fragment;
    auto delete_contents() -> void;
    auto surround_contents(nodes::node* new_parent) -> void;

    auto collapse(ext::boolean_view to_start = false) -> void;
    auto clone_range() const -> range;
    auto is_point_in_range(nodes::node* node, ext::number_view<ulong> offset) const -> bool;

    auto to_json() const -> ext::string;

public js_properties:
    ext::property<nodes::node*> common_ancestor_container;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_properties:
    nodes::node* m_root;

private cpp_accessors:
    auto get_common_ancestor_container() const -> nodes::node*;
};


#endif //SBROWSER2_RANGE_HPP
