#include "extendable_message_event.hpp"
#include "extendable_message_event_private.hpp"

#include <range/v3/view/transform.hpp>


auto service_workers::events::extendable_message_event::get_data() const -> const ext::any&
{
    ACCESS_PIMPL(const extendable_message_event);
    return d->data;
}


auto service_workers::events::extendable_message_event::get_origin() const -> ext::string_view
{
    ACCESS_PIMPL(const extendable_message_event);
    return d->origin;
}


auto service_workers::events::extendable_message_event::get_last_event_id() const -> ext::string_view
{
    ACCESS_PIMPL(const extendable_message_event);
    return d->last_event_id;
}


auto service_workers::events::extendable_message_event::get_source() const -> ext::variant<clients::client*, workers::service_worker*, html::messaging::message_port*>
{
    ACCESS_PIMPL(const extendable_message_event);
    return d->source;
}


auto service_workers::events::extendable_message_event::get_ports() const -> ranges::any_helpful_view<html::messaging::message_port*>
{
    ACCESS_PIMPL(const extendable_message_event);
    return d->ports | ranges::views::transform(&std::unique_ptr<html::messaging::message_port>::get);
}
