#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_TEXT_FORMAT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_TEXT_FORMAT_PRIVATE_HPP

#include "ext/pimpl.ixx"






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


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_TEXT_FORMAT_PRIVATE_HPP
