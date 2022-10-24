#include "svg_graphics_element.hpp"
#include "svg_graphics_element_private.hpp"


auto svg::elements::svg_graphics_element::get_transform() const -> types::svg_animated_transform_list*
{
    ACCESS_PIMPL(const svg_graphics_element);
    return d->transform.get();
}
