#include "privilege.hpp"
#include "privilege_private.hpp"




#include "webappsec_cowl/detail/cowl_internals.hpp"
#include "webappsec_cowl/label.hpp"


webappsec::cowl::privilege::privilege()
{
    INIT_PIMPL(privilege);
}


auto webappsec::cowl::privilege::fresh_privilege() -> std::unique_ptr<privilege>
{
    auto unique_principal = detail::unique_principal();
    auto unique_label = std::make_unique<label>(std::move(unique_principal));
    auto unique_privilege = std::make_unique<privilege>();

    unique_privilege->d_func()->internal_privilege_label = std::move(unique_label);
    return unique_privilege;
}


auto webappsec::cowl::privilege::as_label() -> label*
{
    ACCESS_PIMPL(privilege);
    return d->internal_privilege_label.get();
}


auto webappsec::cowl::privilege::combine(
        webappsec::cowl::privilege* other)
        -> std::unique_ptr<privilege>
{
    ACCESS_PIMPL(privilege);
    decltype(auto) internal_label = d->internal_privilege_label.get();
    decltype(auto) other_label = other->d_func()->internal_privilege_label.get();

    auto combined_privilege = std::make_unique<privilege>();
    combined_privilege->d_func()->internal_privilege_label = internal_label->and_(other_label);
    return combined_privilege;
}


auto webappsec::cowl::privilege::delegate(
        webappsec::cowl::label* other_label)
        -> std::unique_ptr<privilege>
{
    ACCESS_PIMPL(privilege);
    decltype(auto) internal_label = d->internal_privilege_label.get();

    using enum dom::detail::dom_exception_error_t;
    dom::detail::throw_v8_exception<SECURITY_ERR>(
            [internal_label, other_label] {return !internal_label->subsumes(other_label);},
            u8"This privilege's internal label must subsume the 'other' label");

    auto delegated_privilege = std::make_unique<privilege>();
    delegated_privilege->d_func()->internal_privilege_label = internal_label->and_(other_label);
    return delegated_privilege;
}
