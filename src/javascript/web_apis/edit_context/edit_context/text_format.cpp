#include "text_format.hpp"
#include "text_format_private.hpp"
#include "ext/property.hpp"


edit_context::text_format::text_format(detail::touch_format_init_t&& options)
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


auto edit_context::text_format::get_range_start() const -> ext::number<ulong>
{
    ACCESS_PIMPL(const text_format);
    return d->range_start;
}


auto edit_context::text_format::get_range_end() const -> ext::number<ulong>
{
    ACCESS_PIMPL(const text_format);
    return d->range_end;
}


auto edit_context::text_format::get_text_color() const -> ext::string_view
{
    ACCESS_PIMPL(const text_format);
    return d->text_color;
}


auto edit_context::text_format::get_background_color() const -> ext::string_view
{
    ACCESS_PIMPL(const text_format);
    return d->background_color;
}


auto edit_context::text_format::get_underline_style() const -> ext::string_view
{
    ACCESS_PIMPL(const text_format);
    return d->underline_style;
}


auto edit_context::text_format::get_underline_color() const -> ext::string_view
{
    ACCESS_PIMPL(const text_format);
    return d->underline_color;
}


auto edit_context::text_format::get_underline_thickness() const -> ext::string_view
{
    ACCESS_PIMPL(const text_format);
    return d->underline_thickness;
}


auto edit_context::text_format::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .ctor<>()
        .property("rangeStart", &text_format::get_range_start)
        .property("rangeEnd", &text_format::get_range_end)
        .property("textColor", &text_format::get_text_color)
        .property("backgroundColor", &text_format::get_background_color)
        .property("underlineStyle", &text_format::get_underline_style)
        .property("underlineColor", &text_format::get_underline_color)
        .property("underlineThickness", &text_format::get_underline_thickness)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
