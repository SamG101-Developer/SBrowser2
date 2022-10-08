#include "event.hpp"
#include "event_private.hpp"

#include "dom/detail/event_internals.hpp"
#include "hr_time/detail/time_internals.hpp"

#include <range/v3/range/operations.hpp>


dom::events::event::event()
{
    INIT_PIMPL(event);
    // TODO : set some non-parameter-related parameter values
}


dom::events::event::event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
{
    INIT_PIMPL(event);
    ACCESS_PIMPL(event);

    JS_REALM_GET_RELEVANT(this);
    d->type = std::move(event_type);
    d->bubbles = event_init["bubbles"].to<decltype(d->bubbles)>();
    d->cancelable = event_init["cancelable"].to<decltype(d->cancelable)>();
    d->composed = event_init["composed"].to<decltype(d->composed)>();
    d->target = nullptr;
    d->current_target = nullptr;
    d->related_target = nullptr;
    d->event_phase = std::bit_cast<ushort>(NONE);
    d->time_stamp = hr_time::detail::current_hr_time(this_relevant_global_object);
    d->is_trusted = false;
    d->touch_targets = {};
    d->path = {};
}


auto dom::events::event::stop_propagation()
        -> void
{
    // set the stop propagation flag, to stop the event propagating to the next target
    ACCESS_PIMPL(event);
    d->stop_propagation_flag = true;
}


auto dom::events::event::stop_immediate_propagation()
        -> void
{
    // set the stop immediate propagation flag, to stop the event propagating to the next listener
    ACCESS_PIMPL(event);
    d->stop_immediate_propagation_flag = true;
}


auto dom::events::event::prevent_default()
        -> void
{
    // set the cancelled flag if the event is cancelled and isn't in a passive listener
    ACCESS_PIMPL(event);
    d->canceled_flag = d->cancelable && !d->in_passive_listener_flag;
}


auto dom::events::event::composed_path()
        const -> ext::vector<nodes::event_target*>
{
    ACCESS_PIMPL(const event);
    using composed_path_t = ext::vector<nodes::event_target*>;

    // create the default vectors, and return if the current event traversal path is empty
    auto composed_path_vector = composed_path_t{};
    auto path_vector = detail::path_t{};
    if (path_vector.empty())
        return composed_path_vector;

    composed_path_vector.push_back(d->current_target);

    // create the default indexing variables for node identification in the tree
    ext::number<int> current_target_hidden_subtree_level {1};
    ext::number<int> current_hidden_level {0};
    ext::number<int> max_hidden_level {0};

    auto** current_target_index = path_vector.begin();
    auto** iterator             = path_vector.end();

    // loop from the end of the event traversal path to identify the hidden subtree level of the current target
    while (iterator != path_vector.begin())
    {
        auto* path_struct = *iterator;
        if (path_struct->root_of_closed_tree) ++current_target_hidden_subtree_level;
        if (path_struct->invocation_target == d->current_target) {current_target_index = iterator; break;}
        if (path_struct->slot_in_closed_tree) --current_target_hidden_subtree_level;
        ranges::advance(iterator, -1);
    }

    // set the current and max hidden subtree level to the target's hidden subtree level, and the index to the target
    current_hidden_level = current_target_hidden_subtree_level;
    max_hidden_level     = current_target_hidden_subtree_level;
    iterator             = current_target_index - 1;

    // loop from the target to the beginning of the event path, prepending nodes that are in less hidden subtree levels
    while (iterator != path_vector.begin())
    {
        auto* path_struct = *iterator;
        if (path_struct->root_of_closed_tree) ++current_hidden_level;
        if (current_hidden_level <= max_hidden_level) composed_path_vector.push_front(path_struct->invocation_target);
        if (path_struct->slot_in_closed_tree)
        {
            --current_hidden_level;
            max_hidden_level = ext::min(max_hidden_level, current_hidden_level);
        }
        ranges::advance(iterator, -1);
    }

    // set the current and max hidden subtree level to the target's hidden subtree level, and the index to the target
    current_hidden_level = current_target_hidden_subtree_level;
    max_hidden_level     = current_target_hidden_subtree_level;
    iterator             = current_target_index - 1;

    // loop from the target to the end of the event path, appending nodes that are in less hidden subtree levels
    while (iterator != path_vector.end())
    {
        auto* path_struct = *iterator;
        if (path_struct->slot_in_closed_tree) ++current_hidden_level;
        if (current_hidden_level <= max_hidden_level) composed_path_vector.push_back(path_struct->invocation_target);
        if (path_struct->slot_in_closed_tree)
        {
            --current_hidden_level;
            max_hidden_level = ext::min(max_hidden_level, current_hidden_level);
        }
        ranges::advance(iterator, 1);
    }

    // return the generated composed path
    return composed_path_vector;
}


auto dom::events::event::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<event>{isolate}
        .inherit<dom_object>()
        .ctor<ext::string&&, ext::map<ext::string, ext::any>&&>()
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

    return std::move(conversion);
}
