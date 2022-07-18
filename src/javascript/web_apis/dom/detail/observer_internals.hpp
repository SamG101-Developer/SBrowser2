#ifndef SBROWSER2_OBSERVER_INTERNALS_HPP
#define SBROWSER2_OBSERVER_INTERNALS_HPP

#include "ext/any.hpp"
#include "ext/functional.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"

#include <memory>
#include <v8-object.h>
#include <v8-platform.h>
namespace dom::mutations {class mutation_observer;}
namespace dom::nodes {class document;}
namespace dom::nodes {class node;}
namespace html::elements {class html_element; class html_media_element;}


namespace dom::detail::observer_internals
{
    using steps_t = ext::function<void()>;
    enum class mutation_type_t {ATTRIBUTES, CHARACTER_DATA, CHILD_LIST};

    struct registered_observer;
    struct transient_registered_observer;

    // notifications
    auto notify_mutation_observers()
            -> void;

    // queues
    auto queue_microtask(
            steps_t&& steps,
            v8::Isolate* event_loop = nullptr,
            nodes::document* document = nullptr)
            -> void;

    auto queue_mutation_record(
            mutation_type_t type,
            nodes::node* target,
            ext::string_view name,
            ext::string_view namespace_,
            ext::string_view old_value,
            const ext::vector<nodes::node*>& added_nodes,
            const ext::vector<nodes::node*>& removed_nodes,
            nodes::node* previous_sibling,
            nodes::node* next_sibling)
            -> void;

    auto queue_tree_mutation_record(
            nodes::node* target,
            const ext::vector<nodes::node*>& added_nodes,
            const ext::vector<nodes::node*>& removed_nodes,
            nodes::node* previous_sibling,
            nodes::node* next_sibling)
            -> void;

    auto queue_mutation_observer_microtask()
            -> void;

    auto queue_task(
            const v8::Task& task_source,
            steps_t&& steps,
            v8::Isolate* event_loop = nullptr,
            nodes::document* document = nullptr)
            -> void;

    auto queue_global_task(
            const v8::Task& task_source,
            v8::Local<v8::Object> global_object,
            steps_t&& steps)
            -> void;

    auto queue_element_task(
            const v8::Task& task_source,
            html::elements::html_element* element,
            steps_t&& steps)
            -> void;

    auto queue_media_element_task(
            html::elements::html_media_element* element,
            steps_t&& steps)
            -> void;
}


struct dom::detail::observer_internals::registered_observer
{
    std::unique_ptr<mutations::mutation_observer> observer;
    ext::map<ext::string, ext::any> options;
    virtual ~registered_observer() = default;
};


struct dom::detail::observer_internals::transient_registered_observer : public registered_observer
{
    std::unique_ptr<registered_observer> source;
};

#endif //SBROWSER2_OBSERVER_INTERNALS_HPP
