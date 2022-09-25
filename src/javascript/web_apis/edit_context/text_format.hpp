#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_TEXT_FORMAT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_TEXT_FORMAT_HPP

#include "dom_object.hpp"
namespace edit_context {class text_format;}

#include "ext/type_traits.hpp"
#include INCLUDE_INNER_TYPES(edit_context)

#include "edit_context/text_format_private.hpp"


class edit_context::text_format
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(text_format);
    text_format(detail::touch_format_init_t&& options = {});
    MAKE_PIMPL(text_format);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(update_range_start, ext::number<ulong>);
    DEFINE_GETTER(update_range_end, ext::number<ulong>);
    DEFINE_GETTER(selection_start, ext::number<ulong>);
    DEFINE_GETTER(selection_end, ext::number<ulong>);
    DEFINE_GETTER(composition_start, ext::number<ulong>);
    DEFINE_GETTER(composition_end, ext::number<ulong>);
    DEFINE_GETTER(text, ext::string);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_TEXT_FORMAT_HPP
