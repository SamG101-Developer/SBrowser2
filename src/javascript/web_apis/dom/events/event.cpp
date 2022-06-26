#include "event.hpp"

#include <web_apis/dom/detail/event_internals.hpp>


dom::events::event::event(
        ext::string_view event_type,
        ext::string_any_map_view event_init)
        : type(event_type)
        , bubbles(event_init.at("bubbles").value_to_or<ext::boolean>(false))
        , cancelable(event_init.at("cancelable").value_to_or<ext::boolean>(false))
        , composed(event_init.at("composed").value_to_or<ext::boolean>(false))
        , target(nullptr)
        , current_target(nullptr)
        , related_target(nullptr)
        , event_phase(static_cast<ushort>(NONE))
//        , time_stamp(performance::times::dom_high_res_timestamp())
        , is_trusted(false)
        , touch_targets(std::make_unique<touch_targets_t>())
        , path(std::make_unique<path_t>())
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
    auto current_target_hidden_subtree_level = 1;
    auto current_target_index                = path_vector.begin();
    auto current_hidden_level                = 0;
    auto max_hidden_level                    = 0;
    auto iterator                            = path_vector.end();

    // loop from the end of the event traversal path to identify the hidden subtree level of the current target
    while (iterator != path_vector.begin())
    {
        if ((*iterator)->root_of_closed_tree) ++current_target_hidden_subtree_level;
        if ((*iterator)->invocation_target == current_target()) {current_target_index = iterator; break;}
        if ((*iterator)->slot_in_closed_tree) --current_target_hidden_subtree_level;
        --iterator;
    }

    // set the current and max hidden subtree level to the target's hidden subtree level, and the index to the target
    current_hidden_level = current_target_hidden_subtree_level;
    max_hidden_level     = current_target_hidden_subtree_level;
    iterator             = current_target_index - 1;

    // loop from the target to the beginning of the event path, prepending nodes that are in less hidden subtree levels
    while (iterator != path_vector.begin())
    {
        if ((*iterator)->root_of_closed_tree) ++current_hidden_level;
        if (current_hidden_level <= max_hidden_level) composed_path_vector.push_front((*iterator)->invocation_target);
        if ((*iterator)->slot_in_closed_tree)
        {
            --current_hidden_level;
            max_hidden_level = std::min(max_hidden_level, current_hidden_level);
        }
        --iterator;
    }

    // set the current and max hidden subtree level to the target's hidden subtree level, and the index to the target
    current_hidden_level = current_target_hidden_subtree_level;
    max_hidden_level     = current_target_hidden_subtree_level;
    iterator             = current_target_index - 1;

    // loop from the target to the end of the event path, appending nodes that are in less hidden subtree levels
    while (iterator != path_vector.end())
    {
        if ((*iterator)->slot_in_closed_tree) ++current_hidden_level;
        if (current_hidden_level <= max_hidden_level) composed_path_vector.push_back((*iterator)->invocation_target);
        if ((*iterator)->slot_in_closed_tree)
        {
            --current_hidden_level;
            max_hidden_level = std::min(max_hidden_level, current_hidden_level);
        }
        ++iterator;
    }

    // return the generated composed path
    return composed_path_vector;
}


auto dom::events::event::to_v8(
        v8::Isolate* isolate
        ) const && -> ext::any
{
    return v8pp::class_<event>{isolate}
            .ctor<ext::string_view, const ext::string_any_map&>()
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
