#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM__TYPEDEFS_HPP


namespace dom::detail
{
    enum class custom_element_state_t {CUSTOM, UNCUSTOMIZED, PRECUSTOMIZED, UNDEFINED, FAILED, NONE};
    struct custom_element_reactions_stack_t;
    struct custom_element_definition_t;
    struct reaction_t {};
    struct upgrade_reaction_t : public reaction_t {};
    struct callback_reaction_t : public reaction_t {};

    using event_listener_options_t = ext::variant<ext::boolean, ext::map<ext::string, ext::any>>;
    struct event_path_struct_t;

    using exception_condiditional_t = ext::function<bool()>;

    enum class mutation_type_t {ATTRIBUTES, CHARACTER_DATA, CHILD_LIST};
    using steps_t = ext::function<void()>;
    struct registered_observer_t;
    struct transient_registered_observer_t;

    enum boundary_point_comparison_position_t : short {EQUALS = -1, BEFORE = 0, AFTER = 1};
    enum append_action_t {EXTRACT, CLONE};

    enum class traversal_direction_t {NEXT, PREVIOUS};
    enum class traversal_child_t {FIRST_CHILD, LAST_CHILD};
    enum class traversal_sibling_t {NEXT_SIBLING, PREVIOUS_SIBLING};
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM__TYPEDEFS_HPP
