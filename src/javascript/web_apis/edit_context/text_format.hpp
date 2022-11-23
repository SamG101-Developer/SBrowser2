#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_TEXT_FORMAT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_TEXT_FORMAT_HPP

#include "dom_object.hpp"
namespace edit_context {class text_format;}
namespace edit_context {class text_format_private;}

#include "ext/type_traits.hpp"
#include INCLUDE_INNER_TYPES(edit_context)


class edit_context::text_format
        : public virtual dom_object
{
public constructors:
    text_format(detail::touch_format_init_t&& options = {});
    DOM_CTORS(text_format);
    MAKE_PIMPL(text_format);
    MAKE_V8_AVAILABLE(WINDOW);

private js_properties:
    DEFINE_GETTER(range_start, ext::number<ulong>);
    DEFINE_GETTER(range_end, ext::number<ulong>);
    DEFINE_GETTER(text_color, ext::string_view);
    DEFINE_GETTER(background_color, ext::string_view);
    DEFINE_GETTER(underline_style, ext::string_view);
    DEFINE_GETTER(underline_thickness, ext::string_view);
    DEFINE_GETTER(underline_color, ext::string_view);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_TEXT_FORMAT_HPP
