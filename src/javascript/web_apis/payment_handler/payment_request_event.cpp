#include "payment_request_event.hpp"
#include "payment_request_event_private.hpp"

#include "payment_request/payment_request.hpp"


auto payment::handler::payment_request_event::get_top_origin() const -> ext::string_view
{
    ACCESS_PIMPL(const payment_request_event);
    return d->top_origin;
}


auto payment::handler::payment_request_event::get_payment_request_origin() const -> ext::string_view
{
    ACCESS_PIMPL(const payment_request_event);
    return d->payment_request_origin;
}

