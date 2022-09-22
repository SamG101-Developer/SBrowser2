#pragma once
#ifndef SBROWSER2_EVENT_INTERNALS_HPP
#define SBROWSER2_EVENT_INTERNALS_HPP

#include "ext/any.hpp"
#include "ext/boolean.hpp"
#include "ext/concepts.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"
#include "ext/variant.hpp"
#include "ext/vector.hpp"
#include "ext/type_traits.hpp"
#include INCLUDE_INNER_TYPES(dom)
#include <range/v3/view/any_view.hpp>
namespace dom::events {class event;}
namespace dom::nodes {class event_target;}


namespace dom::detail
{
    auto flatten_more(
            ext::variant<ext::map<ext::string, ext::any>, ext::boolean> options)
            -> ext::map<ext::string, ext::any>;

    auto flatten(
            event_listener_options_t&& options)
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
            ext::vector<nodes::event_target*>&& touch_targets,
            ext::boolean  slot_in_closed_tree)
            -> void;

    auto invoke(
            event_path_struct_t* s,
            events::event* event,
            ext::number<uchar> phase)
            -> void;

    auto inner_invoke(
            events::event* event,
            ext::vector_view<ext::map<ext::string, ext::any>> event_listeners,
            ext::number<uchar> phase,
            ext::boolean  invocation_target_in_shadow_tree)
            -> void;

    template <inherit<events::event> T=events::event>
    auto fire_event(
            ext::string&& e,
            nodes::event_target* target,
            ext::map<ext::string, ext::any>&& init = {})
            -> ext::boolean;
}


struct dom::detail::event_path_struct_t
{
    nodes::event_target* invocation_target      = nullptr;
    nodes::event_target* shadow_adjusted_target = nullptr;
    nodes::event_target* related_target         = nullptr;

    ext::vector<nodes::event_target*> touch_targets;
    ext::boolean invocation_target_in_shadow_tree;
    ext::boolean root_of_closed_tree;
    ext::boolean slot_in_closed_tree;

    auto operator==(const event_path_struct_t&) const -> bool = default;
};


#endif //SBROWSER2_EVENT_INTERNALS_HPP
