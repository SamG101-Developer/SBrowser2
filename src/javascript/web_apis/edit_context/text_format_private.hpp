#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_TEXT_FORMAT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_TEXT_FORMAT_PRIVATE_HPP

#include "dom_object_private.hpp"

#include "ext/number.hpp"
#include "ext/pimpl.hpp"
#include "ext/string.hpp"


DEFINE_PRIVATE_CLASS(edit_context, text_format) : dom_object_private
{
    ext::number<ulong> range_start;
    ext::number<ulong> range_end;

    ext::string text_color;
    ext::string background_color;

    ext::string underline_style;
    ext::string underline_thickness;
    ext::string underline_color;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_TEXT_FORMAT_PRIVATE_HPP
