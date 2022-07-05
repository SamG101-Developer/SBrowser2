#pragma once
#ifndef SBROWSER2_EVENT_INTERNALS_HPP
#define SBROWSER2_EVENT_INTERNALS_HPP

#include <variant>
#include <ext/boolean.hpp>
#include <ext/concepts.hpp>
#include <ext/map.hpp>
#include <ext/string.hpp>
#include <ext/vector.hpp>
#include <range/v3/view/any_view.hpp>
namespace dom::events {class event;}
namespace dom::nodes {class event_target;}


namespace dom::detail::event_internals
{
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

    auto flatten_more(
            std::variant<ext::boolean, ext::string_any_map> options)
            -> ext::string_any_map;

    auto flatten(
            std::variant<ext::boolean, ext::string_any_map> options)
            -> ext::boolean;

    auto remove_all_event_listeners(
            nodes::event_target* event_target)
            -> void;

    auto dispatch(
            events::event* event,
            nodes::event_target* target)
            -> ext::boolean;

    auto append_to_event_path(
            events::event* event,
            nodes::event_target* invocation_target,
            nodes::event_target* shadow_adjusted_target,
            nodes::event_target* related_target,
            ranges::any_view<event_path_struct*> touch_targets,
            ext::boolean_view slot_in_closed_tree)
            -> void;

    auto invoke(
            event_path_struct* s,
            events::event* event,
            uchar phase)
            -> void;

    auto inner_invoke(
            events::event* event,
            ranges::any_view<ext::string_any_map> event_listeners,
            uchar phase,
            ext::boolean_view invocation_target_in_shadow_tree)
            -> void;

    template <inherit<events::event> T=events::event>
    static auto fire_event(
            ext::string&& e,
            nodes::event_target* target,
            ext::string_any_map&& init = {})
            -> ext::boolean;
}


#endif //SBROWSER2_EVENT_INTERNALS_HPP
