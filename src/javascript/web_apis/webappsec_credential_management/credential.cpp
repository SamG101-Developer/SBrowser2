#include "credential.hpp"


auto webappsec::credential_management::credential::s_collect_from_credential_store(
        const html::detail::origin_t& origin,
        detail::credential_request_options_t&& options,
        ext::boolean same_origin_with_ancestors)
        -> ext::set<credential*>
{
    return {};
}


auto webappsec::credential_management::credential::s_discover_from_external_source(
        const html::detail::origin_t& origin,
        detail::credential_request_options_t&& options,
        ext::boolean same_origin_with_ancestors)
        -> credential*
{
    return nullptr;
}


auto webappsec::credential_management::credential::s_store(
        credential* credential,
        ext::boolean same_origin_with_ancestors)
        -> class credential*
{
    return nullptr;
}


auto webappsec::credential_management::credential::s_create(
        const html::detail::origin_t& origin,
        detail::credential_request_options_t&& options,
        ext::boolean same_origin_with_ancestors)
        -> credential*
{
    return nullptr;
}
