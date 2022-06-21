#ifndef SBROWSER2_OBSERVER_INTERNALS_HPP
#define SBROWSER2_OBSERVER_INTERNALS_HPP

#include <web_apis/dom/nodes/node.hpp>
namespace html::elements {class html_element; class html_media_element;} // TODO <- IMPORT


namespace dom::detail::observer_internals
{
    using steps_t = std::function<void()>;

    // notifications
    auto notify_mutation_observers()
            -> void;

    // queues
    auto queue_microtask(
            steps_t&& steps)
            -> void;

    auto queue_mutation_record(
            const ext::string& type,
            const nodes::event_target* target,
            const ext::string& name,
            const ext::string& namespace_,
            const ext::string& old_value,
            const ext::vector<nodes::node*>& added_nodes,
            const ext::vector<nodes::node*>& removed_nodes,
            nodes::node* previous_sibling,
            nodes::node* next_sibling)
            -> void;

    auto queue_tree_mutation_record(
            nodes::event_target* target,
            const ext::vector<nodes::node*>& added_nodes,
            const ext::vector<nodes::node*>& removed_nodes,
            nodes::node* previous_sibling,
            nodes::node* next_sibling)
            -> void;

    auto queue_mutation_observers_microtask()
            -> void;

    auto queue_task(
            steps_t&& steps)
            -> void;

    auto queue_global_task(/* TODO */)
            -> void;

    auto queue_element_task(
            html::elements::html_element* element,
            steps_t&& steps)
            -> void;

    auto queue_media_element_task(
            html::elements::html_media_element* element,
            steps_t&& steps)
            -> void;
}

#endif //SBROWSER2_OBSERVER_INTERNALS_HPP
