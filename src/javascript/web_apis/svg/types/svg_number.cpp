#include "svg_number.hpp"
#include "svg_number_private.hpp"





auto svg::types::svg_number::get_value() const -> ext::number<float>
{
    ACCESS_PIMPL(const svg_number);
    return d->value;
}


auto svg::types::svg_number::set_value(ext::number<float> new_value) -> ext::number<float>
{
    ACCESS_PIMPL(svg_number);
    using enum dom::detail::dom_exception_error_t;

    dom::detail::throw_v8_exception<NO_MODIFICATION_ALLOWED_ERR>(
            [d] {return d->readonly;},
            u8"SVGNumber is readonly");

    return d->value = new_value;

    // TODO : reflected element stuff
}
