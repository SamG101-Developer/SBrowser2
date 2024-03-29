module;
#include "ext/macros.hpp"

#include <range/v3/range/operations.hpp>

module apis.dom.event;
import apis.dom.types;

import apis.hr_time.detail;

import ext.core;
import js.env.module_type;
import js.env.realms;


dom::event::event(
        ext::string&& event_type,
        event_init_t&& event_init)
{
    INIT_PIMPL;
    auto e = js::env::env::relevant(this);

    ACCESS_PIMPL;
    d->type = std::move(event_type);
    d->bubbles = event_init[u"bubbles"].to<bool>();
    d->cancelable = event_init[u"cancelable"].to<bool>();
    d->composed = event_init[u"composed"].to<bool>();
    d->target = nullptr;
    d->current_target = nullptr;
    d->related_target = nullptr;
    d->event_phase = std::bit_cast<ushort>(NONE);
    d->time_stamp = hr_time::detail::current_hr_time(e.js.global());
    d->is_trusted = false;
    d->touch_targets = {};
    d->path = {};
}


auto dom::event::stop_propagation() -> void
{
    // Set the 'stop_propagation_flag' stored in the private class - this stops the event propagating to the next target
    // after all the listeners of the 'current_target' have been executed.
    ACCESS_PIMPL;
    d->stop_propagation_flag = true;
}


auto dom::event::stop_immediate_propagation() -> void
{
    // Set the 'stop_immediate_propagation_flag' - this stops the event propagating to the next listener in the
    // 'current_target' ie not all of the listeners will execute in 'current_target'
    ACCESS_PIMPL;
    d->stop_immediate_propagation_flag = true;
}


auto dom::event::prevent_default() -> void
{
    // Set the cancelled flag, as long as the the event is cancelable and isn't in a passive listener - non-cancelable
    // events obviously can't be cancelled, and the 'in_passive_listener_flag' guarantees that an event won't ever be
    // cancelled, even if it is 'cancelable', TODO for performance reasons.
    ACCESS_PIMPL;
    d->canceled_flag = d->cancelable && !d->in_passive_listener_flag;
}


auto dom::event::composed_path() const -> ext::vector<event_target*>
{
    ACCESS_PIMPL;
    using composed_path_t = ext::vector<event_target*>;

    // Create the vectors for the 'composed_path[_vector]' and the 'path[_vector]. If the 'path_vector' is empty, then
    // the 'composed_path_vector' will have to be empty, as there can't be targets in the 'composed_path_vector' that
    // aren't in the 'path_vector' - the 'composed_path_vector' is a subset of the 'path_vector'.
    auto composed_path_vector = composed_path_t{};
    auto path_vector = path_t{};
    if (path_vector.empty())
        return composed_path_vector;

    // Push the current target into 'composed_path_vector'. Note that this will act as the middle of the vector
    // (elements will be pushed behind and infront of the 'current_target', as the event has to traverse down the tree
    // to the 'current_target', and bubble back up (if the 'bubbles' attribute is set).
    composed_path_vector.push_back(d->current_target.get());

    // Create the default indexing variables for node identification in the tree, concerning the shadow tree levels of
    // nodes. 'current_target_hidden_subtree_level' tracks how many layers of "hidden trees" the target resides in; the
    // 'current_hidden_level' is how many hidden levels the current analysis of the nodes has reached; the
    // 'max_hidden_level' is how many hidden levels the analysis of the nodes is allowed to get to.
    ext::number<int> current_target_hidden_subtree_level = 1;
    ext::number<int> current_hidden_level = 0;
    ext::number<int> max_hidden_level = 0;

    // Get the iterators to the beginning of the 'path_vector' (which starts as the current target - added at the start
    // of the method), and the end of the 'path_vector'.
    decltype(auto) current_target_index = path_vector.begin();
    decltype(auto) iterator             = path_vector.end();

    // Iterate from the end of the event's traversal path, to identify the hidden subtree level of the current target.
    // If the next struct in the path is the root of a closed tree, then increase 'current_target_hidden_subtree_level',
    // because a new hidden tree is being entered, and if the struct is a slot, then decrease
    // 'current_target_hidden_subtree_level', because the current hidden tree is being exited from. If the invocation
    // target of the struct is the 'current_target', then break from the looping, so the indexing variables are fixed to
    // the 'current_target'.
    while (iterator != path_vector.end())
    {
        decltype(auto) path_struct = *iterator;
        if (path_struct->root_of_closed_tree) ++current_target_hidden_subtree_level;
        if (path_struct->invocation_target == d->current_target.get()) {current_target_index = iterator; break;}
        if (path_struct->slot_in_closed_tree) --current_target_hidden_subtree_level;
        ranges::advance(iterator, -1);
    }

    // Set the 'current_hidden_level' and 'max_hidden_level' level to the 'current_target_hidden_subtree_level', and the
    // iterator to the target - 1 (start on node before target). This is because this part of the method takes the nodes
    // FROM the 'current_target' TO the beginning of the event's 'path', so the information has to start matching the
    // 'current_target'.
    current_hidden_level = current_target_hidden_subtree_level;
    max_hidden_level     = current_target_hidden_subtree_level;
    iterator             = current_target_index - 1;

    // Loop from the target to the beginning of the event path, prepending nodes that are met. If the prev struct in the
    // path is the root of a closed tree, then increase 'current_target_hidden_subtree_level', because a new hidden tree
    // is being entered, and if the struct is a slot, then decrease 'current_target_hidden_subtree_level', because the
    // current hidden tree is being exited from, and reduce the 'max_hidden_level' to the 'current_hidden_level', so
    // that children that are roots of closed trees aren't entered, ie sibling level hidden trees aren't entered.
    while (iterator != path_vector.begin())
    {
        decltype(auto) path_struct = *iterator;
        if (path_struct->root_of_closed_tree) ++current_hidden_level;
        if (current_hidden_level <= max_hidden_level) composed_path_vector.push_front(path_struct->invocation_target);
        if (path_struct->slot_in_closed_tree)
        {
            --current_hidden_level;
            max_hidden_level = ext::min(max_hidden_level, current_hidden_level);
        }
        ranges::advance(iterator, -1);
    }

    // Set the 'current_hidden_level' and 'max_hidden_level' level to the 'current_target_hidden_subtree_level', and the
    // iterator to the target + 1 (start on node before target). This is because this part of the method takes the nodes
    // FROM the 'current_target' TO the end of the event's 'path', so the information has to start matching the
    // 'current_target'.
    current_hidden_level = current_target_hidden_subtree_level;
    max_hidden_level     = current_target_hidden_subtree_level;
    iterator             = current_target_index + 1;

    // Loop from the target to the end of the event path, appending nodes that are met. If the next struct in the
    // path is the root of a closed tree, then increase 'current_target_hidden_subtree_level', because a new hidden tree
    // is being entered, and if the struct is a slot, then decrease 'current_target_hidden_subtree_level', because the
    // current hidden tree is being exited from, and reduce the 'max_hidden_level' to the 'current_hidden_level', so
    // that children that are roots of closed trees aren't entered, ie sibling level hidden trees aren't entered.
    while (iterator != path_vector.end())
    {
        decltype(auto) path_struct = *iterator;
        if (path_struct->slot_in_closed_tree) ++current_hidden_level;
        if (current_hidden_level <= max_hidden_level) composed_path_vector.push_back(path_struct->invocation_target);
        if (path_struct->slot_in_closed_tree)
        {
            --current_hidden_level;
            max_hidden_level = ext::min(max_hidden_level, current_hidden_level);
        }
        ranges::advance(iterator, 1);
    }

    // Return the generated composed path of 'event_target' objects.
    return composed_path_vector;
}


auto dom::event::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .ctor<ext::string&&, event_init_t&&>()
        .static_("NONE", event::NONE, true)
        .static_("CAPTURING_PHASE", event::CAPTURING_PHASE, true)
        .static_("AT_TARGET", event::AT_TARGET, true)
        .static_("BUBBLING_PHASE", event::BUBBLING_PHASE, true)
        .function("stopImmediatePropagation", &event::stop_immediate_propagation)
        .function("stopPropagation", &event::stop_propagation)
        .function("preventDefault", &event::prevent_default)
        .function("composedPath", &event::composed_path)
        .property("type", &event::get_type)
        .property("bubbles", &event::get_bubbles)
        .property("cancelable", &event::get_cancelable)
        .property("composed", &event::get_composed)
        .property("target", &event::get_target)
        .property("currentTarget", &event::get_current_target)
        .property("relatedTarget", &event::get_related_target)
        .property("eventPhase", &event::get_event_phase)
        .property("timeStamp", &event::get_time_stamp)
        .property("isTrusted", &event::get_is_trusted)
        .property("touchTargets", &event::get_touch_targets)
        .property("path", &event::get_path)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
