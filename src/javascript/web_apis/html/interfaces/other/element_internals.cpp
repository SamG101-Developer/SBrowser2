#include "element_internals.hpp"
#include "element_internals_private.hpp"








auto html::other::element_internals::get_shadow_root() const -> dom::nodes::shadow_root*
{
    ACCESS_PIMPL(const element_internals);

    decltype(auto) target = d->target_element.get();
    return_if (!dom::detail::is_shadow_host(target)) nullptr;

    decltype(auto) shadow = target->d_func()->shadow_root.get();
    return_if (!shadow->d_func()->available_to_element_internals) nullptr;

    return shadow;
}


auto html::other::element_internals::get_form() const -> elements::html_form_element*
{
    ACCESS_PIMPL(const element_internals);
    return d->form_owner.get();
}
