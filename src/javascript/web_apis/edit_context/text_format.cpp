#include "text_format.hpp"
#include "text_format_private.hpp"
#include "ext/property.hpp"


edit_context::text_format::text_format(
        detail::touch_format_init_t&& options)
{
    INIT_PIMPL(text_format);

    ACCESS_PIMPL(text_format);
    d->range_start = options.try_emplace("rangeStart").first->second.to<decltype(d->range_start)>();
    d->range_end = options.try_emplace("rangeEnd").first->second.to<decltype(d->range_end)>();
    d->text_color = options.try_emplace("textColor").first->second.to<decltype(d->text_color)>();
    d->background_color = options.try_emplace("backgroundColor").first->second.to<decltype(d->background_color)>();
    d->underline_style = options.try_emplace("underlineStyle").first->second.to<decltype(d->underline_style)>();
    d->underline_thickness = options.try_emplace("underlineThickness").first->second.to<decltype(d->underline_thickness)>();
    d->underline_color = options.try_emplace("underlineColor").first->second.to<decltype(d->underline_color)>();
}
