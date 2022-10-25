#include "svg_animated_enumeration.hpp"
#include "svg_animated_enumeration_private.hpp"


auto svg::types::svg_animated_enumeration::set_base_val(ext::number<ushort> new_base_val) -> ext::number<ushort>
{
    // TODO : some reflection

    ACCESS_PIMPL(svg_animated_enumeration);
    return d->base_val = new_base_val;
}
