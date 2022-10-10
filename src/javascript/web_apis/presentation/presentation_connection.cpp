#include "presentation_connection.hpp"
#include "presentation_connection_private.hpp"


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
