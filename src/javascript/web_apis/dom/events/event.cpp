#include "event.hpp"

#include "dom/detail/event_internals.hpp"
#include "high_resolution_time/performance.hpp"

#include <range/v3/range/operations.hpp>


dom::events::event::event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : type(event_type)
        , SET_PROPERTY_FROM_OPTIONS(event_init, bubbles, false)
        , SET_PROPERTY_FROM_OPTIONS(event_init, cancelable, false)
        , SET_PROPERTY_FROM_OPTIONS(event_init, composed, false)
        , target(nullptr)
        , current_target(nullptr)
        , related_target(nullptr)
        , event_phase(std::bit_cast<ushort>(NONE))
        , time_stamp(high_resolution_time::performance{}.now())
        , is_trusted(false)
        , touch_targets(touch_targets_t{})
        , path(path_t{})
{}


auto dom::events::event::stop_propagation()
        -> void
{
    // set the stop propagation flag, to stop the event propagating to the next target
    m_stop_propagation_flag = true;
}


auto dom::events::event::stop_immediate_propagation()
        -> void
{
    // set the stop immediate propagation flag, to stop the event propagating to the next listener
    m_stop_immediate_propagation_flag = true;
}


auto dom::events::event::prevent_default()
        -> void
{
    // set the cancelled flag if the event is cancelled and isn't in a passive listener
    m_canceled_flag = cancelable() && !m_in_passive_listener_flag;
}


auto dom::events::event::composed_path()
        const -> ext::vector<nodes::event_target*>
{
    using composed_path_t = ext::vector<nodes::event_target*>;

    // create the default vectors, and return if the current event traversal path is empty
    composed_path_t composed_path_vector{};
    path_t path_vector{};
    if (path_vector.empty())
        return composed_path_vector;

    composed_path_vector.push_back(current_target());

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
        if (path_struct->invocation_target == current_target()) {current_target_index = iterator; break;}
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
        ranges::advance(iterator, -1);;
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
        ranges::advance(iterator, 1);;
    }

    // return the generated composed path
    return composed_path_vector;
}


auto dom::events::event::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<event>{isolate}
            .ctor<ext::string&&, ext::map<ext::string, ext::any>&&>()
            .inherit<dom_object>()
            .static_("NONE", event::NONE, true)
            .static_("CAPTURING_PHASE", event::CAPTURING_PHASE, true)
            .static_("AT_TARGET", event::AT_TARGET, true)
            .static_("BUBBLING_PHASE", event::BUBBLING_PHASE, true)
            .function("stopImmediatePropagation", &event::stop_immediate_propagation)
            .function("stopPropagation", &event::stop_propagation)
            .function("preventDefault", &event::prevent_default)
            .function("composedPath", &event::composed_path)
            .var("type", &event::type, true)
            .var("bubbles", &event::bubbles, true)
            .var("cancelable", &event::cancelable, true)
            .var("composed", &event::composed, true)
            .var("target", &event::target, true)
            .var("currentTarget", &event::current_target, true)
            .var("relatedTarget", &event::related_target, true)
            .var("eventPhase", &event::event_phase, true)
            .var("timeStamp", &event::time_stamp, true)
            .var("isTrusted", &event::is_trusted, true)
            .var("touchTargets", &event::touch_targets, true)
            .var("path", &event::path, true)
            .auto_wrap_objects();
}
