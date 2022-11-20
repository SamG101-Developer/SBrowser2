#include "credentials_container.hpp"
#include "credentials_container_private.hpp"

#include "webappsec_credential_management/detail/algorithm_internals.hpp"


auto webappsec::credential_management::credentials_container::get(
        detail::credential_request_options_t&& options)
        -> ext::promise<credential*>
{
    return detail::request_credential(std::move(options));
}


auto webappsec::credential_management::credentials_container::store(
        credential* credential_object)
        -> ext::promise<credential*>
{
    return detail::store_credential(credential_object);
}


auto webappsec::credential_management::credentials_container::create(
        detail::credential_request_options_t&& options)
        -> ext::promise<credential*>
{
    return detail::create_credential(std::move(options));
}


auto webappsec::credential_management::credentials_container::prevent_silent_access()
        -> ext::promise<void>
{
    auto e = js::env::env::current();
    detail::prevent_silent_access(e);
}
