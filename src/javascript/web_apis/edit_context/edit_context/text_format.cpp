module;
#include "ext/macros/pimpl.hpp"
#include "javascript/macros/expose.hpp"
#include <v8-isolate.h>
#include <v8pp/class.hpp>


module apis.edit_context.text_format;
import apis.edit_context.text_format_private;

import ext.number;
import ext.string;
import ext.tuple;
import js.env.module_type;


edit_context::text_format::text_format(touch_format_init_t&& options)
{
    INIT_PIMPL; ACCESS_PIMPL;
    
    d->range_start = options[u"rangeStart"].to<ulong>();
    d->range_end = options[u"rangeEnd"].to<ulong>();
    d->text_color = options[u"textColor"].to<ulong>();
    d->background_color = options[u"backgroundColor"].to<ulong>();
    d->underline_style = options[u"underlineStyle"].to<ulong>();
    d->underline_thickness = options[u"underlineThickness"].to<ulong>();
    d->underline_color = options[u"underlineColor"].to<ulong>();
}


auto edit_context::text_format::get_range_start() const -> ext::number<ulong>
{
    ACCESS_PIMPL;
    return d->range_start;
}


auto edit_context::text_format::get_range_end() const -> ext::number<ulong>
{
    ACCESS_PIMPL;
    return d->range_end;
}


auto edit_context::text_format::get_text_color() const -> ext::string_view
{
    ACCESS_PIMPL;
    return d->text_color;
}


auto edit_context::text_format::get_background_color() const -> ext::string_view
{
    ACCESS_PIMPL;
    return d->background_color;
}


auto edit_context::text_format::get_underline_style() const -> ext::string_view
{
    ACCESS_PIMPL;
    return d->underline_style;
}


auto edit_context::text_format::get_underline_color() const -> ext::string_view
{
    ACCESS_PIMPL;
    return d->underline_color;
}


auto edit_context::text_format::get_underline_thickness() const -> ext::string_view
{
    ACCESS_PIMPL;
    return d->underline_thickness;
}


auto edit_context::text_format::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
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
