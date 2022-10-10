#include "presentation_connection_available_event.hpp"
#include "presentation_connection_available_event_private.hpp"


presentation::presentation_connection_available_event::presentation_connection_available_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : dom::events::event(std::move(event_type), std::move(event_init))
{
    INIT_PIMPL(presentation_connection_available_event);
    ACCESS_PIMPL(presentation_connection_available_event);

    d->connection = event_init[u8"connection"].to<decltype(d->connection)>();
}


auto presentation::presentation_connection_available_event::get_connection() const -> presentation_connection*
{
    ACCESS_PIMPL(const presentation_connection_available_event);
    return d->connection;
}
