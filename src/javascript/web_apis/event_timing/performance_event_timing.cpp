#include "performance_event_timing.hpp"
#include "performance_event_timing_private.hpp"

#include "ext/casting.hpp"

#include "dom/detail/shadow_internals.hpp"
#include "dom/events/event.hpp"
#include "dom/events/event_private.hpp"
#include "dom/nodes/node.hpp"
#include "dom/nodes/shadow_root.hpp"

#include "pointer_events/pointer_event.hpp"
#include "ui_events/keyboard_event.hpp"

#include "performance_timeline/performance_entry.hpp"


event_timing::performance_event_timing::performance_event_timing()
{
    INIT_PIMPL(performance_event_timing);
}


auto event_timing::performance_event_timing::get_processing_start() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL(const performance_event_timing);
    return d->processing_start;
}


auto event_timing::performance_event_timing::get_processing_end() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL(const performance_event_timing);
    return d->processing_end;
}


auto event_timing::performance_event_timing::get_cancelable() const -> ext::boolean
{
    ACCESS_PIMPL(const performance_event_timing);
    return d->event->d_func()->cancelable;
}


auto event_timing::performance_event_timing::get_target() const -> dom::nodes::node*
{
    ACCESS_PIMPL(const performance_event_timing);
    decltype(auto) node = dynamic_cast<dom::nodes::node*>(d->event_target);
    return node
            && !dom::detail::is_connected(node)
            && !dynamic_cast<dom::nodes::shadow_root*>(dom::detail::shadow_including_root(node))
            ? node : nullptr;
}


auto event_timing::performance_event_timing::get_interaction_id() const -> ext::number<ulonglong>
{
    ACCESS_PIMPL(const performance_event_timing);
    return_if (decltype(auto) pointer_event = dom_cast<pointer_events::pointer_event*>(d->event)) pointer_event->d_func()->pointer_id;
    return_if (decltype(auto) key_event = dom_cast<ui_events::keyboard_event*>(d->event)) key_event->d_func()->code;
    return 0;
}


auto event_timing::performance_event_timing::get_name() const -> ext::string
{
    ACCESS_PIMPL(const performance_event_timing);
    return d->event->d_func()->type;
}


auto event_timing::performance_event_timing::get_entry_type() const -> ext::string
{
    ACCESS_PIMPL(const performance_event_timing);
    return "event"; // TODO : "first-input"?
}


auto event_timing::performance_event_timing::get_start_time() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL(const performance_event_timing);
    return d->event->d_func()->time_stamp;
}


auto event_timing::performance_event_timing::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<performance_event_timing>{isolate}
        .inherit<performance_timeline::performance_entry>()
        .property("processingStart", &performance_event_timing::get_processing_start)
        .property("processingEnd", &performance_event_timing::get_processing_end)
        .property("cancelable", &performance_event_timing::get_cancelable)
        .property("target", &performance_event_timing::get_target)
        .property("interactionId", &performance_event_timing::get_interaction_id)

        .property("name", &performance_event_timing::get_name)
        .property("entryType", &performance_event_timing::get_entry_type)
        .property("startTime", &performance_event_timing::get_start_time)
        .property("duration", &performance_event_timing::get_duration)

        .function("toJSON", &performance_event_timing::operator ext::string)
        .auto_wrap_objects();

    return std::move(conversion);
}
