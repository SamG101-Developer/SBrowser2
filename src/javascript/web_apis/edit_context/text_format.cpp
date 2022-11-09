#include "text_format.hpp"
#include "text_format_private.hpp"
#include "ext/property.hpp"


edit_context::text_format::text_format(
        detail::touch_format_init_t&& options)
{
    INIT_PIMPL(text_format);

    ACCESS_PIMPL(text_format);
    d->range_start = options[u"rangeStart"].to<decltype(d->range_start)>();
    d->range_end = options[u"rangeEnd"].to<decltype(d->range_end)>();
    d->text_color = options[u"textColor"].to<decltype(d->text_color)>();
    d->background_color = options[u"backgroundColor"].to<decltype(d->background_color)>();
    d->underline_style = options[u"underlineStyle"].to<decltype(d->underline_style)>();
    d->underline_thickness = options[u"underlineThickness"].to<decltype(d->underline_thickness)>();
    d->underline_color = options[u"underlineColor"].to<decltype(d->underline_color)>();
}
