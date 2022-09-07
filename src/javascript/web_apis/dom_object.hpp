#ifndef SBROWSER2_DOM_OBJECT_HPP
#define SBROWSER2_DOM_OBJECT_HPP

#include "ext/any.hpp"
#include "ext/custom_operator.hpp"
#include "ext/functional.hpp"
#include "ext/keywords.hpp"
#include "ext/property.hpp"
#include "ext/slot.hpp"
#include "ext/string.hpp"
#include "ext/type_traits.hpp"

#include <memory>
#include <v8-isolate.h>
#include <v8pp/class.hpp>

namespace dom::events {class event;}
namespace dom::nodes {class document;}
namespace dom::nodes {class node;}

#define behaviour_method(...) ext::function<void(__VA_ARGS__)>

#define DOM_CTORS(type)  \
    DISALLOW_COPY(type); \
    ALLOW_MOVE(type)


class dom_object
{
public constructors:
    dom_object() = default;
    virtual ~dom_object() = default;

public cpp_methods:
    virtual auto to_v8(v8::Isolate* isolate) const && -> ext::any = 0;
    virtual auto to_json() const -> ext::string {return "";}

public cpp_properties:
    struct // TODO : move to dom::nodes::event_target
    {
        behaviour_method(
                dom::events::event* event_causing_activation)
                activation_behaviour;

        behaviour_method(
                dom::nodes::node* node_to_remove)
                remove_steps;

        behaviour_method(
                dom::nodes::node* clone,
                dom::nodes::document* document_to_clone_into,
                ext::boolean&& deep_clone)
                cloning_steps;

        behaviour_method(
                ext::string local_name,
                ext::string old_value,
                ext::string new_value,
                ext::string namespace_)
                attribute_change_steps;

        behaviour_method()
                adopting_steps;

        behaviour_method()
                children_changed_steps;

        behaviour_method()
                insertion_steps;

    } m_dom_behaviour;
};


inline auto dom_object::to_v8(v8::Isolate* isolate) const && -> ext::any
{
    return v8pp::class_<dom_object>{isolate}.auto_wrap_objects();
}


#endif //SBROWSER2_DOM_OBJECT_HPP
