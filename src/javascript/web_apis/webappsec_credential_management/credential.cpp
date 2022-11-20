#include "credential.hpp"
#include "credential_private.hpp"

#include "web_idl/detail/type_mapping_internals.hpp"


auto webappsec::credential_management::credential::is_conditional_mediation_available() -> ext::promise<ext::boolean>
{
    auto e = js::env::env::current(); // TODO : which realm?
    return web_idl::detail::create_resolved_promise(ext::boolean::FALSE_(), e.js.realm());
}


auto webappsec::credential_management::credential::get_id() const -> ext::string_view
{
    ACCESS_PIMPL(const credential);
    return d->id;
}


auto webappsec::credential_management::credential::get_type() const -> ext::string_view
{
    ACCESS_PIMPL(const credential);
    return d->type;
}
