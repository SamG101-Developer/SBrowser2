#include "svg_geometry_element.hpp"
#include "svg_geometry_element_private.hpp"


auto svg::elements::svg_geometry_element::get_path_length() const -> types::svg_animated_number*
{
    ACCESS_PIMPL(const svg_geometry_element);
    return d->path_lengths.get();
}
