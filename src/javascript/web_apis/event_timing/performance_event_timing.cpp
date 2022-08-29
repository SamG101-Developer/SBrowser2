#include "performance_event_timing.hpp"

#include "dom/detail/shadow_internals.hpp"
#include "dom/events/event.hpp"
#include "dom/nodes/node.hpp"
#include "dom/nodes/shadow_root.hpp"


auto event_timing::performance_event_timing::get_cancelable()
        const -> decltype(this->cancelable)::value_t
{
    return m_event->cancelable();
}


auto event_timing::performance_event_timing::get_target()
        const -> decltype(this->target)::value_t
{
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
