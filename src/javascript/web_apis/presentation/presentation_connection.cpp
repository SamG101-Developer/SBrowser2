#include "presentation_connection.hpp"
#include "presentation_connection_private.hpp"

#include INCLUDE_INNER_TYPES(presentation)

#include "presentation/detail/presentation_internals.hpp"


auto presentation::presentation_connection::close() -> void
{
    ACCESS_PIMPL(presentation_connection);
    detail::start_closing_presentation_connection(this, detail::presentation_connection_close_reason::CLOSED, u8"");
}


auto presentation::presentation_connection::terminate() -> void
{
    ACCESS_PIMPL(presentation_connection);
    detail::in_controlling_browsing_context(this) && detail::terminate_presentation_in_controlling_browsing_context(this);
    detail::in_receiving_browsing_context(this)   && detail::terminate_presentation_in_receiving_browsing_context(this);
}


auto presentation::presentation_connection::get_id() const -> ext::string_view
{
    ACCESS_PIMPL(const presentation_connection);
    return d->presentation_identifier;
}


auto presentation::presentation_connection::get_url() const -> ext::string_view
{
    ACCESS_PIMPL(const presentation_connection);
    return d->presentation_url;
}


auto presentation::presentation_connection::get_state() const -> detail::presentation_connection_state_t
{
    ACCESS_PIMPL(const presentation_connection);
    return d->current_state;
}


auto presentation::presentation_connection::get_binary_type() const -> ext::string_view
{
    ACCESS_PIMPL(const presentation_connection);
    return d->binary_type;
}
