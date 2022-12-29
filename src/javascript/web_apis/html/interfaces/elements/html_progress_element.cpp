#include "html_progress_element.hpp"
#include "html_progress_element_private.hpp"




auto html::elements::html_progress_element::get_value() const -> ext::number<double>
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_progress_element);
        return detail::is_indeterminate_progress_bar(this) ? 0 : d->value;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_progress_element::get_max() const -> ext::number<double>
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_progress_element);
        return d->max;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_progress_element::get_position() const -> ext::number<double>
{
    ACCESS_PIMPL(const html_progress_element);
    return detail::is_indeterminate_progress_bar(this) ? -1 : d->value / d->max;
}


auto html::elements::html_progress_element::set_value(ext::number<double> new_value) -> ext::number<double>
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_progress_element);
        return d->value = new_value > 0 && new_value < d->max ? new_value : d->value;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_progress_element::set_max(ext::number<double> new_max) -> ext::number<double>
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_progress_element);
        return d->max = new_max;
    CE_REACTIONS_METHOD_EXE
}
