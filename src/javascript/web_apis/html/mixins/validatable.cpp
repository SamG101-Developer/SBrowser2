#include "validatable.hpp"
#include "validatable_private.hpp"

#include "ext/casting.hpp"

#include "dom/detail/event_internals.hpp"
#include "html/elements/html_element.hpp"


auto html::mixins::validatable::check_validity() -> ext::boolean
{
    if (detail::candidate_for_constraint_validation(this) && ! detail::satitisfies_constaints(this))
    {
        decltype(auto) cast_this = dom_cross_cast<html::elements::html_element*>(this);
        dom::detail::fire_event(u8"invalid", cast_this, {{u8"cancelable", true}});
        return false;
    }

    return true;
}


auto html::mixins::validatable::get_will_validate() const -> ext::boolean
{
    return detail::candidate_for_constraint_validation(this);
}


auto html::mixins::validatable::get_validity() const -> other::validity_state*
{
    ACCESS_PIMPL(const validatable);
    return d->validity_state.get();
}


auto html::mixins::validatable::get_validation_message() const -> ext::string
{
    return detail::candidate_for_constraint_validation(this) || detail::satisfies_constraints(this)
            ? u8""
            : u8"TODO : useful message";
}
