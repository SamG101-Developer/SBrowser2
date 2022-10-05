#include "payment_request.hpp"
#include "payment_request_private.hpp"


payment::request::payment_request::payment_request(
        ext::vector_span<detail::payment_method_data_t*> method_data,
        detail::payment_method_init_t&& details)
{
    INIT_PIMPL(payment_request);

    JS_REALM_GET_CURRENT
}
