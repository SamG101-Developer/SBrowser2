module;
#include <memory>
#include <function2/function2.hpp>
#include <swl/variant.hpp>


export module apis.dom.types;
import ext.any;
import ext.boolean;
import ext.functional;
import ext.map;
import ext.number;
import ext.string;
import ext.tuple;
import ext.variant;
import ext.vector;

namespace dom {class event;}
namespace dom {class mutation_observer;}
namespace dom {class mutation_record;}
namespace dom {class element;}
namespace dom {class event_target;}
namespace dom {class node;}
namespace html {class html_script_element;}
namespace svg {class svg_script_element;}


export namespace dom::detail
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
    enum class traversal_direction_t {NEXT, PREVIOUS};
    enum class traversal_child_t {FIRST_CHILD, LAST_CHILD};
    enum class traversal_sibling_t {NEXT_SIBLING, PREVIOUS_SIBLING};
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
    using event_listener_options_t = ext::map<ext::string, ext::any>;
    using add_event_listener_options_t = ext::map<ext::string, ext::any>;
    using exception_condiditional_t = ext::function<bool()>;
    using event_listener_callback_t = ext::function<void(ext::string, event*), void()>;
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

