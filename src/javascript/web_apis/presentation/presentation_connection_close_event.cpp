#include "presentation_connection_close_event.hpp"
#include "presentation_connection_close_event_private.hpp"

#include INCLUDE_INNER_TYPES(presentation)


presentation::presentation_connection_close_event::presentation_connection_close_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : dom::events::event{std::move(event_type), std::move(event_init)}
{
    INIT_PIMPL(presentation_connection_close_event);

    ACCESS_PIMPL(presentation_connection_close_event);
    d->reason = event_init[u8"reason"].to<detail::presentation_connection_close_reason>();
    d->message = std::move(event_init[u8"message"].to<ext::string>());
}
