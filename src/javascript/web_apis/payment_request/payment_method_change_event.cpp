#include "payment_method_change_event.hpp"
#include "payment_method_change_event_private.hpp"


payment::request::payment_method_change_event::payment_method_change_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : payment_request_update_event{std::move(event_type), std::move(event_init)}
{
    INIT_PIMPL(payment_method_change_event);
    ACCESS_PIMPL(payment_method_change_event);

    d->method_name    = event_init[u8"method_name"].to<decltype(d->method_name)>();
    d->method_details = event_init[u8"method_details"].to<decltype(d->method_name)>();
}


auto payment::request::payment_method_change_event::get_method_name() const -> ext::string_view
{
    ACCESS_PIMPL(const payment_method_change_event);
    return d->method_name;
}


auto payment::request::payment_method_change_event::get_method_details() const -> ext::string_view
{
    ACCESS_PIMPL(const payment_method_change_event);
    return d->method_details;
}
