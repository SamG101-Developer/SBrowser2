#include "presentation_availability.hpp"
#include "presentation_availability_private.hpp"


presentation::presentation_availability::presentation_availability()
{
    INIT_PIMPL(presentation_availability);
}


auto presentation::presentation_availability::get_value() const -> ext::boolean
{
    ACCESS_PIMPL(const presentation_availability);
    return d->value;
}
