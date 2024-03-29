module;
#include "ext/macros.hpp"


export module apis.edit_context.text_format;
import apis.dom_object;


DEFINE_PUBLIC_CLASS(edit_context, text_format) final
        : public virtual dom_object
{
public typedefs:
    using touch_format_init_t = ext::map<ext::string, ext::any>;

public constructors:
    text_format(touch_format_init_t&& options = {});
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
