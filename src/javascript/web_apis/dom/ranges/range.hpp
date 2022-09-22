#ifndef SBROWSER2_RANGE_HPP
#define SBROWSER2_RANGE_HPP

#include "dom/ranges/abstract_range.hpp"
namespace dom::node_ranges {class range;}

#include "ext/type_traits.hpp"
namespace dom::nodes {class document_fragment;}
namespace dom::detail {auto contains(nodes::node*, const node_ranges::range*) -> ext::boolean;}
namespace dom::detail {auto set_start_or_end(node_ranges::range*, nodes::node*, ext::number<ulong>, ext::boolean ) -> void;}

#include "dom/ranges/range_private.hpp"


class dom::node_ranges::range
        : public abstract_range
{
public friends:
    friend auto dom::detail::contains(
            nodes::node* new_container, const node_ranges::range* range) -> ext::boolean;

    friend auto dom::detail::set_start_or_end(
            node_ranges::range* range, nodes::node* new_container, ext::number<ulong> new_offset,
            ext::boolean  start) -> void;

public constructors:
    range();

public js_static_constants:
    constexpr static const ext::number<short> START_TO_START = 0;
    constexpr static const ext::number<short> START_TO_END = 1;
    constexpr static const ext::number<short> END_TO_END = 2;
    constexpr static const ext::number<short> END_TO_START = 3;

public js_methods:
    auto set_start(nodes::node* new_container, ext::number<ulong> new_offset) -> void;
    auto set_start_before(nodes::node* new_container) -> void;
    auto set_start_after(nodes::node* new_container) -> void;

    auto set_end(nodes::node* new_container, ext::number<ulong> new_offset) -> void;
    auto set_end_before(nodes::node* new_container) -> void;
    auto set_end_after(nodes::node* new_container) -> void;

    auto insert_node(nodes::node* new_container) -> nodes::node*;
    auto intersects_node(nodes::node* container) const -> ext::boolean;
    auto select_node(nodes::node* container) -> void;
    auto select_node_contents(nodes::node* container) -> void;

    auto compare_boundary_points(ext::number<ushort> how, range* source_range) -> ext::number<short>;
    auto compare_point(nodes::node* container, ext::number<ulong> offset) const -> ext::number<short>;
    auto is_point_in_range(nodes::node* container, ext::number<ulong> offset) const -> ext::boolean;

    auto extract_contents() -> nodes::document_fragment*;
    auto clone_contents() -> nodes::document_fragment*;
    auto delete_contents() -> nodes::document_fragment*;
    auto surround_contents(nodes::node* parent) -> nodes::document_fragment*;

    auto collapse(ext::boolean  to_start = false) -> void;
    auto clone_range() const -> range;

    /* DOM_PARSING */
    auto create_contextual_fragmnt(ext::string&& fragment) -> nodes::document_fragment;

public js_properties:
    ext::property<nodes::node*> common_ancestor_container;

public cpp_members:
    MAKE_PIMPL(range);
    MAKE_V8_AVAILABLE;
    MAKE_STRINGIFIER;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(common_ancestor_container);
};


#endif //SBROWSER2_RANGE_HPP
