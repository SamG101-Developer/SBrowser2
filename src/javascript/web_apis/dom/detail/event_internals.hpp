#pragma once
#ifndef SBROWSER2_EVENT_INTERNALS_HPP
#define SBROWSER2_EVENT_INTERNALS_HPP

#include <variant>

#include <ext/any.hpp>
#include <ext/boolean.hpp>
#include <ext/map.hpp>
#include <ext/string.hpp>
#include <ext/type_traits.hpp>
#include <ext/vector.hpp>

#include <web_apis/dom/abort/abort_signal.hpp>
#include <web_apis/dom/nodes/event_target.hpp>

#include <range/v3/view/remove_if.hpp>

namespace dom::events {class event;}
namespace dom::nodes {class event_target;}


namespace dom::detail::event_internals
{
    auto flatten_more(
            std::variant<ext::boolean, ext::string_any_map> options)
            -> ext::string_any_map;

    auto flatten(
            std::variant<ext::boolean, ext::string_any_map> options)
            -> ext::boolean;

    auto add_event_listener(
            nodes::event_target* event_target,
            const ext::string_any_map& event_listener)
            -> void;

    auto remove_event_listener(
            nodes::event_target* event_target,
            const ext::string_any_map& event_listener)
            -> void;

    auto remove_all_event_listeners(
            nodes::event_target* event_target)
            -> void;

    auto dispatch(
            events::event* event,
            nodes::event_target* event_target)
            -> ext::boolean;

    struct event_path_struct
    {
        nodes::event_target* invocation_target      = nullptr;
        nodes::event_target* shadow_adjusted_target = nullptr;
        nodes::event_target* related_target         = nullptr;

        ext::vector<nodes::event_target*> touch_targets;
        ext::boolean invocation_target_in_shadow_tree;
        ext::boolean root_of_closed_tree;
        ext::boolean slot_in_closed_tree;

        auto operator==(const event_path_struct&) const -> bool = default;
    };
}


auto dom::detail::event_internals::flatten_more(
        std::variant<ext::boolean, ext::string_any_map> options)
        -> ext::string_any_map
{
    // return {capture: true} if the options is a bool value, otherwise the map already being held in the variant
    return std::holds_alternative<ext::boolean>(options)
           ? ext::string_any_map{std::make_pair("capture", std::get<ext::boolean>(options))}
           : std::get<ext::string_any_map>(options);
}


auto dom::detail::event_internals::flatten(
        std::variant<ext::boolean, ext::string_any_map> options)
        -> ext::boolean
{
    // return the boolean if a boolean value is being stored in the variant, otherwise the capture option of the map
    return std::holds_alternative<ext::boolean>(options)
           ? std::get<ext::boolean>(options)
           : std::get<ext::string_any_map>(options).at("capture").value().to<ext::boolean>();
}


auto dom::detail::event_internals::add_event_listener(
        nodes::event_target* event_target,
        const ext::string_any_map& event_listener)
        -> void
{
    // get the abort signal from the event listener, and default the object to nullptr if it doesn't exist in the map
    auto* signal = event_listener.at("signal").value_to_or<abort::abort_signal*>(nullptr);

    // return if
    //  - there is no callback - invoking the event listener would have no effect and would waste cycles
    //  - there is a signal that has already aborted, - no need for the event listener to exist
    //  - the event listener is already stored in the event listeners list - no duplicates allowed
    if (event_listener.at("callback").empty()
        || signal && signal->aborted()
        || std::ranges::find(event_target->m_event_listeners, event_listener) != event_target->m_event_listeners.end())
        return;

    // append the event listener to the event listeners list and if there is an abort signal, add an abort algorithm
    // that removes the event_listener from the event_target->m_event_listeners list
    event_target->m_event_listeners.push_back(event_listener);
    if (signal)
        signal->m_abort_algorithms.push_back([&event_listener, &event_target] {remove_event_listener(event_target, event_listener);});
}


auto dom::detail::event_internals::remove_event_listener(
        nodes::event_target* event_target,
        const ext::string_any_map& event_listener)
        -> void
{
    // set the removed attribute of the listener to true (so if the listener is being held in a variable it can be
    // detected that it is no longer in use)
    ext::string r {"removed"};
    event_listener.insert_or_assign(r, ext::boolean::FALSE());

    // alias the callback type for convenience, and remove all event listeners that have a matching callback, type and
    // capture attribute to event_listener
    using callback_t = typename nodes::event_target::event_listener_callback_t;
    event_target->m_event_listeners |= ranges::views::remove_if([event_listener](const ext::string_any_map& existing_listener)
    {
        return existing_listener.at("callback")->to<callback_t>() == event_listener.at("callback")->to<callback_t>()
               && existing_listener.at("type")->to<ext::string_view>() == event_listener.at("type")->to<ext::string_view>()
               && existing_listener.at("capture")->to<ext::boolean>() == event_listener.at("capture")->to<ext::boolean>();
    });
}


auto dom::detail::event_internals::remove_all_event_listeners(
        nodes::event_target* event_target)
        -> void
{
    // iterate over the event listeners, and remove each one from the event target sing the predefined removal
    // algorithm defined above (not just popping items from a list)
    for (const ext::string_any_map& existing_listener: event_target->m_event_listeners)
        remove_event_listener(event_target, existing_listener);
}



#endif //SBROWSER2_EVENT_INTERNALS_HPP
