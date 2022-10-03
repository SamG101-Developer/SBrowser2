#include "can_make_payment_event.hpp"


auto payment::handler::can_make_payment_event::get_top_origin() const -> ext::string_view
{
    ACCESS_PIMPL(const can_make_payment_event);
    return d->top_origin;
}


auto payment::handler::can_make_payment_event::get_payment_request_origin() const -> ext::string_view
{
    ACCESS_PIMPL(const can_make_payment_event);
    return d->payment_request_origin;
}


auto payment::handler::can_make_payment_event::get_method_data() const -> ext::vector_span<detail::payment_method_data_t>
{
    ACCESS_PIMPL(const can_make_payment_event);
    return d->method_data;
}
