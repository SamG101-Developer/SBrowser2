module;
#include "ext/macros.hpp"
#include <memory>
#include <function2/function2.hpp>
#include <swl/variant.hpp>


export module apis.dom.types;
import ext.core;


DEFINE_FWD_DECL_NAMESPACE(dom)
{
    class abstract_iterator;

    class abstract_range;
    class abort_controller;
    class abort_signal;
    class attr;
    class cdata_section;
    class character_data;
    class custom_event;
    class comment;
    class document;
    class document_fragment;
    class document_type;
    class dom_exception;
    class dom_implementation;
    class element;
    class event_target;
    class event;
    class mutation_observer;
    class mutation_record;
    class node;
    class node_filter;
    class node_iterator;
    class processing_instruction;
    class range;
    class shadow_root;
    class static_range;
    class text;
    class tree_walker;
    class window;
    class window_proxy;
    class xml_document;
}


DEFINE_FWD_DECL_NAMESPACE_MIXINS(dom)
{
    class child_node;
    class document_or_element_node;
    class document_or_shadow_root;
    class non_document_type_child_node;
    class non_element_parent_node;
    class parentable_node;
    class slottable;
}


DEFINE_FWD_DECL_NAMESPACE_DETAIL(dom)
{
    struct custom_element_reactions_stack_t;
    struct custom_element_definition_t;
    struct reaction_t {};
    struct upgrade_reaction_t : public reaction_t {};
    struct callback_reaction_t : public reaction_t {};
    struct event_path_struct_t;
    struct registered_observer_t;
    struct transient_registered_observer_t;
    struct boundary_point_t;
    struct xpath_ns_resolver_t;

    enum class custom_element_state_t {CUSTOM, UNCUSTOMIZED, PRECUSTOMIZED, UNDEFINED, FAILED, NONE};
    enum class mutation_type_t {ATTRIBUTES, CHARACTER_DATA, CHILD_LIST};
    enum boundary_point_comparison_position_t : short {EQUALS = -1, BEFORE = 0, AFTER = 1};
    enum append_action_t {EXTRACT, CLONE};
    enum class shadow_root_mode_t {OPEN, CLOSED};
    enum class slot_assignment_mode_t {MANUAL, NAMED};
    enum class dom_exception_error_t {INDEX_SIZE_ERR, DOMSTRING_SIZE_ERR, HIERARCHY_REQUEST_ERR, WRONG_DOCUMENT_ERR,
            INVALID_CHARACTER_ERR, NO_DATA_ALLOWED_ERR, NO_MODIFICATION_ALLOWED_ERR, NOT_FOUND_ERR, NOT_SUPPORTED_ERR,
            INUSE_ATTRIBUTE_ERR, INVALID_STATE_ERR, SYNTAX_ERR, INVALID_MODIFICATION_ERR, NAMESPACE_ERR,
            INVALID_ACCESS_ERR, VALIDATION_ERR, TYPE_MISMATCH_ERR, SECURITY_ERR, NETWORK_ERR, ABORT_ERR,
            URL_MISMATCH_ERR, QUOTA_EXCEEDED_ERR, TIMEOUT_ERR, INVALID_NODE_TYPE_ERR, DATA_CLONE_ERR, ENCODING_ERR,
            NOT_READABLE_ERR, UNKNOWN_ERR, CONSTRAINT_ERR, DATA_ERR, TRANSACTION_INACTIVE_ERR, READONLY_ERR,
            VERSION_ERR, OPERATION_ERR, NOT_ALLOWED_ERR, /* [MEDIA-CAPTURE-MAIN] */ OVERCONSTRAINED_ERR};

    using abort_signal_callback_t  = ext::function<void()>;
    using abort_signal_callbacks_t = ext::vector<abort_signal_callback_t>;
    using exception_condiditional_t = ext::function<bool()>;

    // using module_map_t = ext::map<ext::tuple<ext::string, url::detail::url_t*>, ext::string>;
    using html_or_svg_script_element_t = ext::variant<std::unique_ptr<html::html_script_element>, std::unique_ptr<svg::svg_script_element>>;
    using lifecycle_callback_t = ext::function<void()>;
    using html_element_constructor_t = ext::function<element*()>;
}


export enum class v8_primitive_error_t
{
    V8_TYPE_ERROR, V8_RANGE_ERROR, V8_REFERENCE_ERROR, V8_SYNTAX_ERROR, V8_WASM_COMPILE_ERROR, V8_WASM_LINK_ERROR,
    V8_WASM_RUNTIME_ERROR,
    V8_DATA_ERROR /* TODO <-- These don't have a v8 type yet */
};


struct dom::detail::event_path_struct_t
{
    event_target* invocation_target      = nullptr;
    event_target* shadow_adjusted_target = nullptr;
    event_target* related_target         = nullptr;

    ext::vector<event_target*> touch_targets;
    ext::boolean invocation_target_in_shadow_tree;
    ext::boolean root_of_closed_tree;
    ext::boolean slot_in_closed_tree;

    auto operator==(const event_path_struct_t&) const -> bool = default;
};


export struct dom::detail::boundary_point_t
{
    std::observer_ptr<node> node;
    ext::number<ulong> offset;
};


struct dom::detail::registered_observer_t
{
    std::unique_ptr<mutation_observer> observer;
    ext::map<ext::string, ext::any> options;
};


struct dom::detail::transient_registered_observer_t : public registered_observer_t
{
    std::unique_ptr<registered_observer_t> source;
};

