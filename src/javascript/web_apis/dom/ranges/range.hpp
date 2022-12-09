#ifndef SBROWSER2_RANGE_HPP
#define SBROWSER2_RANGE_HPP


namespace dom::node_ranges {class range;}
namespace dom::node_ranges {class range_private;}


namespace dom::nodes {class document_fragment;}


class dom::node_ranges::range
        : public abstract_range
{
public friends:
    friend class dom::nodes::node;

public constructors:
    range();
    MAKE_PIMPL(range);
    MAKE_V8_AVAILABLE(WINDOW);
    MAKE_STRINGIFIER;

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

    auto extract_contents() -> std::unique_ptr<nodes::document_fragment>;
    auto clone_contents() -> std::unique_ptr<nodes::document_fragment>;
    auto delete_contents() -> void;
    auto surround_contents(nodes::node* parent) -> std::unique_ptr<nodes::document_fragment>;

    auto collapse(ext::boolean  to_start = false) -> void;
    auto clone_range() const -> std::unique_ptr<range>;

    /* [DOM-PARSING] */
    auto create_contextual_fragmnt(ext::string&& fragment) -> nodes::document_fragment;

private js_properties:
    DEFINE_GETTER(common_ancestor_container, nodes::node*);
};


#endif //SBROWSER2_RANGE_HPP
