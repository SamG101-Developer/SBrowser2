#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_TEXT_FORMAT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_TEXT_FORMAT_HPP

#include "dom_object.hpp"
namespace edit_context {class text_format;}

#include "ext/type_traits.hpp"
#include INCLUDE_INNER_TYPES(edit_context)


class edit_context::text_format
        : public dom_object
{
public constructors:
    DOM_CTORS(text_format);
    text_format() = default;
    text_format(detail::touch_format_init_t&& options = {});

public js_properties:
    ext::property<ext::number<ulong>> range_start;
    ext::property<ext::number<ulong>> range_end;
    ext::property<ext::string> text_color;
    ext::property<ext::string> background_color;
    ext::property<ext::string> underline_style;
    ext::property<ext::string> underline_thickness;
    ext::property<ext::string> underline_color;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_TEXT_FORMAT_HPP
