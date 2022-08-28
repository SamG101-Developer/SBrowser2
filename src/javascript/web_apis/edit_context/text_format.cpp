#include "text_format.hpp"
#include "ext/property.hpp"


edit_context::text_format::text_format(
        detail::touch_format_init_t&& options)
        : SET_PROPERTY_FROM_OPTIONS_NO_DEFAULT(options, range_start)
        , SET_PROPERTY_FROM_OPTIONS_NO_DEFAULT(options, range_end)
        , SET_PROPERTY_FROM_OPTIONS_NO_DEFAULT(options, text_color)
        , SET_PROPERTY_FROM_OPTIONS_NO_DEFAULT(options, background_color)
        , SET_PROPERTY_FROM_OPTIONS_NO_DEFAULT(options, underline_style)
        , SET_PROPERTY_FROM_OPTIONS_NO_DEFAULT(options, underline_thickness)
        , SET_PROPERTY_FROM_OPTIONS_NO_DEFAULT(options, underline_color)
{}
