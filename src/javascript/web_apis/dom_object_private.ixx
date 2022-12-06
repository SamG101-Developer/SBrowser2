module;
#include "ext/macros/pimpl.hpp"
#include <function2/function2.hpp>


export module apis._.dom_object_private;
import ext.boolean;
import ext.functional;
import ext.memory;
import ext.string;

class dom_object;
namespace dom {class document;}
namespace dom {class element;}
namespace dom {class event;}
namespace dom {class node;}

#define BEHAVIOUR_METHOD(...) ext::function<void(__VA_ARGS__) const>


export struct dom_object_private
{
    MAKE_QIMPL(dom_object);

    BEHAVIOUR_METHOD(
            dom::event* event_causing_activation)
            activation_behaviour;

    BEHAVIOUR_METHOD(
            dom::node* node_to_remove)
            remove_steps;

    BEHAVIOUR_METHOD(
            dom::node* clone,
            dom::document* document_to_clone_into,
            ext::boolean deep_clone)
            cloning_steps;

    BEHAVIOUR_METHOD(
            ext::string_view local_name,
            ext::string_view old_value,
            ext::string_view new_value,
            ext::string_view namespace_)
            attribute_change_steps;

    BEHAVIOUR_METHOD()
            adopting_steps;

    BEHAVIOUR_METHOD()
            children_changed_steps;

    BEHAVIOUR_METHOD()
            insertion_steps;

    BEHAVIOUR_METHOD()
            environment_discarding_steps;

    virtual ~dom_object_private() {q_ptr.reset();};

protected:
    std::observer_ptr<dom_object> q_ptr;
};
