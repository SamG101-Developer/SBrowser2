module;
#include "ext/macros/pimpl.hpp"


export module apis.dom.node_private;
import apis.dom.event_target_private;
import ext.boolean;
import ext.number;
import ext.vector;
import ext.memory;

namespace dom {class document;}
namespace html {class html_slot_element;}


DEFINE_PRIVATE_CLASS(dom, node)
        : event_target_private
{
    MAKE_QIMPL(node);

    ext::vector<std::unique_ptr<detail::registered_observer_t>> registered_observer_list;
    std::observer_ptr<document> node_document;

    ext::vector<std::unique_ptr<node>> child_nodes;
    std::observer_ptr<node> parent_node;
    
    auto root() const -> node*;
    auto ancestors() const -> ranges::any_helpful_view<node*>;
    auto descendants() -> ranges::any_helpful_view<node*>;
    
    auto is_ancestor(const node* other) const -> ext::boolean;
    auto is_descendant(const node* other) const -> ext::boolean;

    auto is_sibling(const node* other) const -> ext::boolean;
    auto is_preceding(const node* other) const -> ext::boolean;
    auto is_following(const node* other) const -> ext::boolean;
    
    auto index() const -> ext::number<ulong>;
    auto length() const -> ext::number<ulong>;
    
    auto first_child() const -> node*;
    auto last_child() const -> node*;
    auto previous_sibling() const -> node*;
    auto next_sibling() const -> node*;

    template <typename T=node> auto all_following() const -> ranges::any_helpful_view<T*>;
    template <typename T=node> auto all_preceding() const -> ranges::any_helpful_view<T*>;
    template <typename T=node> auto all_following_siblings() const -> ranges::any_helpful_view<T*>;
    template <typename T=node> auto all_preceding_siblings() const -> ranges::any_helpful_view<T*>;

    virtual auto is_element_node() const -> ext::boolean;
    virtual auto is_text_node() const -> ext::boolean;
    virtual auto is_exclusive_text_node() const -> ext::boolean;
    virtual auto is_document_type_node() const -> ext::boolean;

    auto contiguous_text_nodes() const -> ranges::any_helpful_view<text*>;
    auto descendant_text_nodes() const -> ranges::any_helpful_view<text*>;
    auto child_text_nodes() const -> ranges::any_helpful_view<text*>;

    auto contiguous_text_content() const -> ext::string;
    auto descendant_text_content() const -> ext::string;
    auto child_text_content() const -> ext::string;

    auto common_ancestor(const nodes::node* other) const -> node*;
    auto is_document_element() const -> ext::boolean;

    auto is_connected() const -> ext::boolean;
    auto is_slot() const -> ext::boolean;
    auto is_slottable() const -> ext::boolean;
    auto is_assigned() const -> ext::boolean;

    auto is_root_shadow_root() const -> nodes::shadow_root*;
    auto is_shadow_root() const -> ext::boolean;
    auto is_shadow_host() const -> ext::boolean;

    auto shadow_including_descendants() const -> ranges::any_helpful_view<node*>;
    auto is_shadow_including_descendant(const nodes::node* other) const -> ext::boolean;
    auto is_shadow_including_ancestor(const nodes::node* other) const -> ext::boolean;
    auto is_host_including_ancestor(const nodes::node* other) -> ext::boolean;
    auto is_closed_shadow_hidden(const nodes::node* other) const -> ext::boolean;

    auto signal_slot_change() const -> void;
    auto shadow_including_root() const -> nodes::node*;
    auto shadow_root() const -> shadow_root*;

    auto assign_slot() const -> void;
    auto find_slot(ext::boolean open_flag = false) const -> html::html_slot_element*;

    auto list_of_elements_with_qualified_name(ext::string_view qualified_name) const -> ext::vector<element*>;
    auto list_of_elements_with_namespace_and_local_name(ext::string_view namespace_, ext::string_view local_name) const -> ext::vector<element*>;
    auto list_of_elements_with_class_names(ext::string_view class_names) const -> ext::vector<element*>;
    auto string_replace_all(ext::string_view string) -> void;
};
