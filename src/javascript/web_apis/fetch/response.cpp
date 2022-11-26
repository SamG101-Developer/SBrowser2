#include "response.hpp"
#include "response_private.hpp"

#include "fetch/detail/body_internals.hpp"
#include "fetch/detail/response_internals.hpp"
#include "fetch/headers.hpp"


fetch::response::response(detail::body_init_t&& body, detail::response_init_t&& init)
{
    INIT_PIMPL(response);
    ACCESS_PIMPL(response);

    d->response = std::make_unique<detail::response_t>();
    d->headers = std::make_unique<headers>(d->response->header_list, detail::header_guard_t::RESPONSE);

    if (!ext::holds_alternative<ext::variant_monostate_t>(std::move(body)))
        detail::initialize_response_object(this, std::move(init), detail::extract(std::move(body)));
}
