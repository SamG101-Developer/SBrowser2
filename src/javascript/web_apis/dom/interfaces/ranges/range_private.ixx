module;
#include "ext/macros.hpp"
#include <tuplet/tuple.hpp>


export module apis.dom.range:p;
import apis.dom.abstract_range;
import apis.dom.types;

IMPORT_ALL_TYPES(dom);


DEFINE_PRIVATE_CLASS(dom, range) final
        : abstract_range_private
{
public:
    MAKE_QIMPL(range);
    friend class dom::character_data_private;
    
public:
    auto root() const -> node*;

    // Containment and position checks
    auto contains(node* new_container) const -> ext::boolean;
    auto partially_contains(node* new_container) const -> ext::boolean;
    auto set_start_or_end(node* new_container, ext::number<ulong> new_offset, ext::boolean at_start) -> void;
    auto position_relative(node* start_container, ext::number<ulong> start_offset, node* end_container, ext::number<ulong> end_offset) const -> detail::boundary_point_comparison_position_t;

    // Other general helper methods for ranges
    template <ext::inherit<character_data> T> auto copy_data(T* child, document_fragment* fragment, character_data* container, ext::number<ulong> start_offset, ext::number<ulong> end_offset, ext::boolean  replace) const -> document_fragment*;
    auto get_range_containment_children(node* start_container, node* end_container) const -> ext::tuple<node*, node*, ranges::any_helpful_view<node*>>;
    auto append_to_sub_fragment(node* child, document_fragment* fragment, node* start_container, ext::number<ulong> start_offset, node* end_container, ext::number<ulong> end_offset, detail::append_action_t what) const -> std::unique_ptr<document_fragment>;
    auto create_new_node_and_offset(node* start_container, node* end_container, ext::number<ulong> start_offset) const -> ext::tuple<node*, ext::number<ulong>>;
};
