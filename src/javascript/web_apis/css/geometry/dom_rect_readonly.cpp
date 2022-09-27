#include "dom_rect_readonly.hpp"


auto css::geometry::dom_rect_readonly::get_x() const -> ext::number<double>
{
    ACCESS_PIMPL(const dom_rect_readonly);
    return d->matrix.x();
}
