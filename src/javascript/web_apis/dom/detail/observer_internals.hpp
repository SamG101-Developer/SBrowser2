#ifndef SBROWSER2_OBSERVER_INTERNALS_HPP
#define SBROWSER2_OBSERVER_INTERNALS_HPP

#include "ext/any.hpp"
#include "ext/functional.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"
#include "html/_typedefs.hpp"
#include INCLUDE_INNER_TYPES(dom)
#include INCLUDE_INNER_TYPES(html)

#include <memory>
#include <v8-forward.h>
namespace dom::mutations {class mutation_observer;}
namespace dom::nodes {class document;}
namespace dom::nodes {class node;}
namespace html::elements {class html_element; class html_media_element;}


namespace dom::detail
{

    // notifications
    auto notify_mutation_observers()
            -> void;

    // queues
    template <typename F>
    auto queue_microtask(
            F&& steps,
            v8::Isolate* event_loop = nullptr,
            nodes::document* document = nullptr)
            -> void;

    auto queue_mutation_record(
            mutation_type_t type,
            nodes::node* target,
            const std::string& name,
            const std::string& namespace_,
            const std::string& old_value,
            ext::vector<nodes::node*>&& added_nodes,
            ext::vector<nodes::node*>&& removed_nodes,
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

    template <typename F>
    auto queue_task(
            html::detail::task_queue_t& task_source,
            F&& steps,
            v8::Isolate* event_loop = nullptr,
            nodes::document* document = nullptr)
            -> void;

    template <typename F>
    auto queue_global_task(
            html::detail::task_queue_t& task_source,
            v8::Local<v8::Object> global_object,
            F&& steps)
            -> void;

    template <typename F>
    auto queue_element_task(
            html::detail::task_queue_t& task_source,
            const html::elements::html_element* element,
            F&& steps)
            -> void;

    template <typename F>
    auto queue_media_element_task(
            const html::elements::html_media_element* element,
            F&& steps)
            -> void;
}


struct dom::detail::registered_observer_t
{
    std::unique_ptr<mutations::mutation_observer> observer;
    ext::map<ext::string, ext::any> options;
};


struct dom::detail::transient_registered_observer_t : public registered_observer_t
{
    std::unique_ptr<registered_observer_t> source;
};


#endif //SBROWSER2_OBSERVER_INTERNALS_HPP
