module;
#include "ext/macros.hpp"
#include <function2/function2.hpp>
#include <tuplet/tuple.hpp>

export module apis.dom.detail;
import apis.dom.types;
import apis.html.types;
import ext.core;
import js.env.realms;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(dom)
{
    namespace namespaces
    {
        /* [DOM] */
        inline constexpr auto HTML = u"http://www.w3.org/1999/xhtml";
        inline constexpr auto MATHML = u"http://www.w3.org/1998/Math/MathML";
        inline constexpr auto SVG = u"http://www.w3.org/2000/svg";
        inline constexpr auto XLINK = u"http://www.w3.org/1999/xlink";
        inline constexpr auto XML = u"http://www.w3.org/XML/1998/namespace";
        inline constexpr auto XMLNS = u"http://www.w3.org/2000/xmlns/";
        inline constexpr auto NONE = u"";

        /* [N3] */
        inline constexpr auto DC = u"http://purl.org/dc/elements/1.1/";
        inline constexpr auto FOAF = u"http://xmlns.com/foaf/0.1/";
        inline constexpr auto EX = u"http://www.example.org/#";
        inline constexpr auto I18N = u"https://www.w3.org/ns/i18n#";
        inline constexpr auto RDF = u"http://www.w3.org/1999/02/22-rdf-syntax-ns#";
        inline constexpr auto RDFS = u"http://www.w3.org/2000/01/rdf-schema#";
        inline constexpr auto XSD = u"http://www.w3.org/2001/XMLSchema#";
    }

    // [1.1] - Trees
    auto root(const node* a) -> node*;
    auto descendants(const node* a) -> ranges::any_helpful_view<node*>;
    auto ancestors(const node* a) -> ranges::any_helpful_view<node*>;
    auto is_inclusive_descendant(const node* a, node* b) -> ext::boolean;
    auto is_inclusive_ancestor(const node* a, node* b) -> ext::boolean;

    auto is_sibling(const node* a, node* b) -> ext::boolean;
    auto is_preceding(const node* a, node* b) -> ext::boolean;
    auto is_following(const node* a, node* b) -> ext::boolean;

    auto index(const node* a) -> ext::number<ulong>;

    auto first_child(const node* a) -> node*;
    auto last_child(const node* a) -> node*;
    auto previous_sibling(const node* a) -> node*;
    auto next_sibling(const node* a) -> node*;

    template <typename T=node> auto all_following(const node* a) -> ranges::any_helpful_view<T*>;
    template <typename T=node> auto all_preceding(const node* a) -> ranges::any_helpful_view<T*>;
    template <typename T=node> auto all_following_siblings(const node* a) -> ranges::any_helpful_view<T*>;
    template <typename T=node> auto all_preceding_siblings(const node* a) -> ranges::any_helpful_view<T*>;

    // [1.4] - Namespaces
    auto validate(ext::string_view qualified_name) -> void;
    auto validate_and_extract(ext::string_view namespace_, ext::string_view qualified_name) -> ext::tuple<ext::string, ext::string>;
    auto html_adjust_string(ext::string&& string, ext::boolean adjust, ext::boolean lower = true) -> ext::string;

    // [2.7] - EventTarget
    auto flatten_more(ext::map<ext::string, ext::any>&& options) -> ext::map<ext::string, ext::any>;
    auto flatten_more(ext::boolean options) -> ext::map<ext::string, ext::any>;
    auto flatten(event_listener_options_t&& options) -> ext::boolean;
    auto flatten(ext::boolean options) -> ext::boolean;

    auto default_passive_value(ext::string_view event_type, event_target* target) -> ext::boolean;
    auto add_event_listener(event_target* target, event_listener_t&& listener) -> void;
    auto remove_event_listener(event_target* target, event_listener_t&& listener) -> void;
    auto remove_all_event_listener(event_target* target) -> void;

    // [2.9] - Dispatching Events
    auto dispatch(event* event, event_target* target) -> ext::boolean;
    auto append_to_event_path(event* event, event_target* invocation_target, event_target* shadow_adjusted_target, event_target* related_target, ext::vector<event_target*>&& touch_targets, ext::boolean slot_in_closed_tree) -> void;
    auto invoke(event* event, detail::event_path_struct_t& s, ext::number<uchar> phase) -> void;
    auto inner_invoke(event* event, ext::span<ext::map<ext::string, ext::any>> event_listeners, ext::number<uchar> phase, ext::boolean invocation_target_in_shadow_tree) -> void;

    // [2.10] - Firing Events
    template <ext::inherit<event> T=event>
    auto fire_event(ext::string&& e, dom::event_target* target, ext::map<ext::string, ext::any>&& init = {}) -> ext::boolean;

    // [3.2] - Aborting
    auto aborted(abort_signal* signal) -> ext::boolean;
    auto follow_signal(abort_signal* following_signal, abort_signal* parent_signal) -> void;
    auto signal_abort(abort_signal* signal, ext::any&& reason) -> void;

    // [4.2] - Node Tree
    auto length(const node* a) -> ext::number<ulong>;
    auto empty(const node* a) -> ext::boolean;

    // [4.2.1] - Document Tree
    auto is_document_element() -> ext::boolean;
    auto element_in_document_tree(element* element) -> ext::boolean;

    // [4.2.2] - Shadow Tree TODO : attribute update steps for name (slots & slottables)
    auto is_connected(node* node) -> ext::boolean;

    auto is_slot() -> ext::boolean;
    auto is_slottable() -> ext::boolean;
    auto is_assigned() -> ext::boolean;

    auto find_slot(ext::boolean open_flag = false) -> html::html_slot_element*;
    auto find_slottables(const html::html_slot_element* slot) -> ranges::any_helpful_view<dom::mixins::slottable*>;
    auto find_flattened_slottables(const html::html_slot_element* slot) -> ranges::any_helpful_view<dom::mixins::slottable*>;

    auto assign_slottables(const html::html_slot_element* slot) -> void;
    auto assign_slottables_for_tree(const html::html_slot_element* descendant) -> void;
    auto assign_slot() -> void;

    auto signal_slot_change() -> void;

    // [4.2.3] - Mutation Algorithms
    auto common_checks(const node* node_, node* parent, node* child) -> void;
    auto ensure_pre_insertion_validity(const node* node_, node* parent, node* child) -> void;
    auto pre_insert(std::unique_ptr<node> node_, node* parent, node* child) -> node*;
    auto pre_remove(const node* node_, node* parent) -> node*;
    auto insert(std::unique_ptr<node>&& node_, node* parent, node* child, ext::boolean  suppress_observers_flag = false) -> node*;
    auto append(std::unique_ptr<node>&& node_, node* parent) -> node*;
    auto replace(std::unique_ptr<node>&& node_, node* parent, node* child) -> node*;
    auto replace_all(std::unique_ptr<node>&& node_, node* parent) -> void;
    auto remove(const node* node_, ext::boolean suppress_observers_flag = false) -> node*;

    // [4.2.6] - ParentNode
    auto convert_nodes_into_node(ext::type_is<node*, ext::string> auto&&... nodes) -> node*;

    // [4.3] - Mutation Observers
    auto queue_mutation_observer_microtask() -> void;
    auto notify_mutation_observers() -> void;

    auto queue_mutation_record(mutation_type_t type, node* target, ext::string_view name, ext::string_view namespace_, ext::string_view old_value, ext::span<node*> added_nodes, ext::span<node*> removed_nodes, node* previous_sibling, node* next_sibling) -> void;
    auto queue_tree_mutation_record(node* target, ext::span<node*> added_nodes, ext::span<node*> removed_nodes, node* previous_sibling, node* next_sibling) -> void;

    // [4.4] - Node
    auto string_replace_all(const node* node, ext::string_view string) -> void;
    auto clone(const node* node_, document* document = nullptr, ext::boolean deep = false) -> std::unique_ptr<node>;
    
    auto locate_a_namespace_prefix(const node* node, ext::string_view namespace_) -> ext::string;
    auto locate_a_namespace(const node* node, ext::string_view prefix) -> ext::string;

    auto list_of_elements_with_qualified_name(node* node, ext::string_view qualified_name) -> ext::vector<element*>;
    auto list_of_elements_with_namespace_and_local_name(node* node, ext::string_view namespace_, ext::string_view local_name) -> ext::vector<element*>;
    auto list_of_elements_with_class_names(node* node, ext::string_view class_names) -> ext::vector<element*>;

    // [4.5] - Document
    auto element_interface(ext::string_view name, ext::string_view namespace_) -> std::unique_ptr<node>;
    auto adopt(node* node_, document* document) -> node*;

    // [4.7] - DocumentFragment
    auto is_host_including_ancestor(const node* a, node* b) -> ext::boolean;

    // [4.8] - ShadowRoot
    auto shadow_including_root(const node* a) -> node*;
    auto shadow_including_descendants(const node* a) -> ranges::any_helpful_view<node*>;
    auto is_shadow_including_descendant(const node* a, node* b) -> ext::boolean;
    auto is_shadow_including_ancestor(const node* a, node* b) -> ext::boolean;
    auto is_closed_shadow_hidden(const node* a, node* b) -> ext::boolean;
    auto retarget(const event_target* a, event_target* b) -> event_target*;

    // [4.9] - Element TODO attribute update steps for element->d_func()->id
    auto create_element(document* document, ext::string_view local_name, ext::string_view namespace_, ext::string_view prefix = u"", ext::boolean is = false, ext::boolean synchronous_custom_element_flag = false) -> std::unique_ptr<element>;
    auto handle_attributes_changes(attr* attribute, element* owner_element, ext::string_view old_value, ext::string_view new_value) -> void;
    auto change( attr* attribute, ext::string&& new_value) ->  attr*;
    auto append(std::unique_ptr<attr>&& attribute,  element* new_owner_element) ->  attr*;
    auto remove( attr* attribute) -> std::unique_ptr<attr>;
    auto replace(attr* old_attribute, std::unique_ptr<attr>&& new_attribute) ->  attr*;

    auto get_attribute_by_name(ext::string_view qualified_name, const element* element) -> attr*;
    auto get_attribute_by_namespace_and_local_name(ext::string_view namespace_, ext::string_view local_name, const element* element) -> attr*;
    auto get_attribute_value(const element* element, ext::string_view local_name, ext::string_view namespace_ = u"") -> ext::string_view;
    auto set_attribute(std::unique_ptr<attr>&& attribute, element* element) -> attr*;
    auto set_attribute_value(element* element, ext::string_view local_name, ext::string&& value, ext::string_view prefix = u"", ext::string_view namespace_ = u"") -> void;
    auto remove_attribute_by_name(ext::string_view qualified_name, element* element) -> std::unique_ptr<attr>;
    auto remove_attribute_by_namespace_and_local_name(ext::string_view namespace_, ext::string_view local_name, element* element) -> std::unique_ptr<attr>;
    auto insert_adjacent(element* element, ext::string_view where, node* node_) -> node*;

    // [4.10] - CharacterData
    auto replace_data(character_data* node, ext::number<ulong> offset, ext::number<ulong> count, ext::string&& new_data) -> void;
    auto substring_data(const character_data* node, ext::number<ulong> offset, ext::number<ulong> count) -> ext::string;

    // [4.11] - Text
    auto is_exclusive_text_node(const node* a) -> ext::boolean;
    auto contiguous_text_nodes(const text* text_node) -> ranges::any_helpful_view<text*>;
    auto contiguous_text_content(const text* text_node) -> ext::string;
    auto descendant_text_nodes(const text* text_node) -> ranges::any_helpful_view<text*>;
    auto descendant_text_content(const text* text_node) -> ext::string;
    auto child_text_nodes(const text* text_node) -> ranges::any_helpful_view<text*>;
    auto child_text_content(const text* text_node) -> ext::string;
    auto split(text* node, ext::number<ulong> offset) -> std::unique_ptr<text>;

    // [4.12] - Ranges
    auto position_relative(const node* start_container, ext::number<ulong> start_offset, node* end_container, ext::number<ulong> end_offset) -> boundary_point_comparison_position_t;
    auto is_range_collapsed(const abstract_range* range) -> ext::boolean;
    auto root(const range*) -> node*;
    auto contains(const range* range, node* new_container) -> ext::boolean;
    auto partially_contains(const range* range, node* new_container) -> ext::boolean;
    auto set_start_or_end(abstract_range* range, node* new_container, ext::number<ulong> new_offset, ext::boolean at_start) -> void;
    auto select(const node* node, const abstract_range* range) -> void;

    // [6] - Traversal
    auto filter(const abstract_iterator* iterator, const node* node) -> ext::number<ushort>;
    auto traverse(const node_iterator* iterator, traversal_direction_t direction) -> node*;
    auto traverse_children(const tree_walker* walker, traversal_child_t type) -> node*;
    auto traverse_siblings(const tree_walker* walker, traversal_sibling_t type) -> node*;

    // Other
    template <ext::inherit<character_data> T> auto copy_data(T* child, document_fragment* fragment, character_data* container, ext::number<ulong> start_offset, ext::number<ulong> end_offset, ext::boolean  replace) -> document_fragment*;
    auto get_range_containment_children(node* start_container, node* end_container) -> ext::tuple<node*, node*, ranges::any_helpful_view<node*>>;
    auto append_to_sub_fragment(node* child, document_fragment* fragment, node* start_container, ext::number<ulong> start_offset, node* end_container, ext::number<ulong> end_offset, detail::append_action_t what) -> std::unique_ptr<document_fragment>;
    auto create_new_node_and_offset(node* start_container, node* end_container, ext::number<ulong> start_offset) -> ext::tuple<node*, ext::number<ulong>>;
    auto common_ancestor(const node* a, const node* b) -> node*;

    auto is_root_shadow_root() -> shadow_root*;
    auto is_shadow_root() -> ext::boolean;
    auto is_shadow_host() -> ext::boolean;
    auto shadow_root() -> shadow_root*;

    auto is_html() -> ext::boolean;
    auto qualified_name() -> ext::string;
    auto html_uppercase_qualified_name() -> ext::string;
    auto html_lowercase_qualified_name() -> ext::string;


    template <v8_primitive_error_t T>
    auto throw_v8_exception(ext::unique_function<auto() -> bool>&& condition, ext::u8string&& message, js::env::env& e) -> void;
    template <dom_exception_error_t T>
    auto throw_v8_exception(ext::unique_function<auto() -> bool>&& condition, ext::u8string&& message, js::env::env& e) -> void;
    auto throw_v8_exception(dom::dom_exception&& exception) -> void;
}
