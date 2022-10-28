#include "html_meter_element.hpp"
#include "html_meter_element_private.hpp"

#include "dom/detail/customization_internals.hpp"


auto html::elements::html_meter_element::get_value() const -> ext::number<double>
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_meter_element);
        return d->actual_value;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_meter_element::get_min() const -> ext::number<double>
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_meter_element);
        return d->minimum_value;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_meter_element::get_max() const -> ext::number<double>
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_meter_element);
        return d->maximum_value;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_meter_element::get_low() const -> ext::number<double>
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_meter_element);
        return d->low_boundary;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_meter_element::get_high() const -> ext::number<double>
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_meter_element);
        return d->high_boundary;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_meter_element::get_optimum() const -> ext::number<double>
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_meter_element);
        return d->optimum_point;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_meter_element::set_value(ext::number<double> new_value) -> ext::number<double>
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_meter_element);
        return d->actual_value = new_value;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_meter_element::set_min(ext::number<double> new_min) -> ext::number<double>
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_meter_element);
        return d->minimum_value = new_min;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_meter_element::set_max(ext::number<double> new_max) -> ext::number<double>
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_meter_element);
        return d->maximum_value = new_max;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_meter_element::set_low(ext::number<double> new_low) -> ext::number<double>
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_meter_element);
        return d->low_boundary = new_low;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_meter_element::set_high(ext::number<double> new_high) -> ext::number<double>
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_meter_element);
        return d->high_boundary = new_high;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_meter_element::set_optimum(ext::number<double> new_optimum) -> ext::number<double>
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_meter_element);
        return d->optimum_point = new_optimum;
    CE_REACTIONS_METHOD_EXE
}
