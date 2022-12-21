module;
#include "ext/macros/pimpl.hpp"


export module apis.edit_context.text_format_private;
import apis.dom_object_private;

import ext.core;


DEFINE_PRIVATE_CLASS(edit_context, text_format)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(text_format);

public:
    ext::number<ulong> range_start;
    ext::number<ulong> range_end;

    ext::string text_color;
    ext::string background_color;

    ext::string underline_style;
    ext::string underline_thickness;
    ext::string underline_color;
};
