#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_OBJECT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_OBJECT_PRIVATE_HPP

#define BEHAVIOUR_METHOD(...) ext::function<void(__VA_ARGS__) const>

namespace dom::nodes {class document;}
namespace dom::nodes {class element;}
namespace dom::nodes {class node;}


struct dom_object_private
{
    BEHAVIOUR_METHOD(
            dom::events::event* event_causing_activation)
            activation_behaviour;

    BEHAVIOUR_METHOD(
            dom::nodes::node* node_to_remove)
            remove_steps;

    BEHAVIOUR_METHOD(
            dom::nodes::node* clone,
            dom::nodes::document* document_to_clone_into,
            ext::boolean deep_clone)
            cloning_steps;

    BEHAVIOUR_METHOD(
            ext::string local_name,
            ext::string old_value,
            ext::string new_value,
            ext::string namespace_)
            attribute_change_steps;

    BEHAVIOUR_METHOD()
            adopting_steps;

    BEHAVIOUR_METHOD()
            children_changed_steps;

    BEHAVIOUR_METHOD()
            insertion_steps;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_OBJECT_PRIVATE_HPP
