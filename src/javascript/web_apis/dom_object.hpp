#ifndef SBROWSER2_DOM_OBJECT_HPP
#define SBROWSER2_DOM_OBJECT_HPP

#include "ext/any.hpp"
#include "ext/custom_operator.hpp"
#include "ext/functional.hpp"
#include "ext/keywords.hpp"
#include "ext/pimpl.hpp"
#include "ext/property.hpp"
#include "ext/slot.hpp"
#include "ext/string.hpp"
#include "ext/type_traits.hpp"

#include "dom_object_private.hpp"

#include <memory>
#include <v8-isolate.h>
#include <v8pp/class.hpp>

namespace dom::nodes {class document;}
namespace dom::nodes {class element;}
namespace dom::nodes {class node;}


#define BEHAVIOUR_METHOD(...) ext::function<void(__VA_ARGS__) const>


#define DOM_CTORS(type)  \
    DISALLOW_COPY(type); \
    ALLOW_MOVE(type)


#define MAKE_V8_AVAILABLE \
public:                   \
    SELF_MACRO_DEFINE_SELF(self_t, public);\
    static auto to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>


#define MAKE_STRINGIFIER \
public:                  \
    operator ext::string() const


class dom_object
{
public constructors:
    dom_object() = default;
    virtual ~dom_object() = default;

public:
    struct
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

    } m_dom_behaviour;

private cpp_members:
    MAKE_V8_AVAILABLE;
    MAKE_STRINGIFIER {return "";}
};


auto dom_object::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<dom_object>{isolate}.auto_wrap_objects();
    return std::move(conversion);
}


#endif //SBROWSER2_DOM_OBJECT_HPP
