#include "performance_event_timing.hpp"

#include "dom/detail/shadow_internals.hpp"
#include "dom/events/event.hpp"
#include "dom/nodes/node.hpp"
#include "dom/nodes/shadow_root.hpp"

#include "performance_timeline/performance_entry.hpp"


event_timing::performance_event_timing::performance_event_timing()
{
    bind_get(processing_start);
    bind_get(processing_end);
    bind_get(cancelable);
    bind_get(target);
    bind_get(interaction_id);
    bind_get(name);
    bind_get(entry_type);
    bind_get(start_time);
    bind_get(duration);
}


auto event_timing::performance_event_timing::get_cancelable()
        const -> decltype(this->cancelable)::value_t
{
    // The 'cancelable' getter of this class maps to the event's 'cancelable' property (like a forwarding method).
    return m_event->cancelable();
}


auto event_timing::performance_event_timing::get_target()
        const -> decltype(this->target)::value_t
{
    // The 'target' property maps to the target of the event, given that the event's 'target' is a Node object that is
    // not connected, and isn't a ShadowRoot, otherwise return nullptr.
    decltype(auto) target_node = dynamic_cast<dom::nodes::node*>(m_event->target());
    return target_node
            && !dom::detail::is_connected(target_node)
            && !dynamic_cast<dom::nodes::shadow_root*>(dom::detail::shadow_including_root(target_node))
            ? target_node : nullptr;
}


auto event_timing::performance_event_timing::get_name() const -> decltype(this->name)::value_t
{return m_event->type();}

auto event_timing::performance_event_timing::get_start_time() const -> decltype(this->start_time)::value_t
{return m_event->time_stamp();}


auto event_timing::performance_event_timing::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<performance_event_timing>{isolate}
        .inherit<performance_timeline::performance_entry>()
        .var("processingStart", &performance_event_timing::processing_start, true)
        .var("processingEnd", &performance_event_timing::processing_end, true)
        .var("cancelable", &performance_event_timing::cancelable, true)
        .var("target", &performance_event_timing::target, true)
        .var("interactionId", &performance_event_timing::interaction_id, true)
        .function("toJSON", &performance_event_timing::to_json)
        .auto_wrap_objects();
}
