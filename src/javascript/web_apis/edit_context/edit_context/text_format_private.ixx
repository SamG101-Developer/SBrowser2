module;
#include "ext/macros/pimpl.hpp"


export module apis.edit_context.text_format_private;
import apis._.dom_object_private;

import ext.number;
import ext.string;



DEFINE_PRIVATE_CLASS(edit_context, text_format)
        : virtual dom_object_private
{
    MAKE_QIMPL(text_format);

    ext::number<ulong> range_start;
    ext::number<ulong> range_end;

    ext::string text_color;
    ext::string background_color;

    ext::string underline_style;
    ext::string underline_thickness;
    ext::string underline_color;
};
