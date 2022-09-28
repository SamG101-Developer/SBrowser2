#include "dom_rect_readonly.hpp"


auto css::geometry::dom_rect_readonly::get_x() const -> ext::number<double>
{
    ACCESS_PIMPL(const dom_rect_readonly);
    return d->rect.x();
}


auto css::geometry::dom_rect_readonly::get_y() const -> ext::number<double>
{
    ACCESS_PIMPL(const dom_rect_readonly);
    return d->rect.y();
}


auto css::geometry::dom_rect_readonly::get_w() const -> ext::number<double>
{
    ACCESS_PIMPL(const dom_rect_readonly);
    return d->rect.width();
}


auto css::geometry::dom_rect_readonly::get_h() const -> ext::number<double>
{
    ACCESS_PIMPL(const dom_rect_readonly);
    return d->rect.height();
}


auto css::geometry::dom_rect_readonly::get_top() const -> ext::number<double>
{
    ACCESS_PIMPL(const dom_rect_readonly);
    return d->rect.top();
}


auto css::geometry::dom_rect_readonly::get_right() const -> ext::number<double>
{
    ACCESS_PIMPL(const dom_rect_readonly);
    return d->rect.right();
}


auto css::geometry::dom_rect_readonly::get_bottom() const -> ext::number<double>
{
    ACCESS_PIMPL(const dom_rect_readonly);
    return d->rect.bottom();
}


auto css::geometry::dom_rect_readonly::get_left() const -> ext::number<double>
{
    ACCESS_PIMPL(const dom_rect_readonly);
    return d->rect.left();
}

