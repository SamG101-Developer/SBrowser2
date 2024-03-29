module;
#include "ext/macros.hpp"


export module apis.edit_context.text_format_update_event;
import apis.dom.event;

IMPORT_ALL_TYPES(edit_context);


DEFINE_PUBLIC_CLASS(edit_context, text_format_update_event) final
        : public dom::event
{
public typedefs:
    using text_format_update_event_init_t = ext::map<ext::string, ext::any>;

public constructors:
    text_format_update_event(ext::string&& event_type, text_format_update_event_init_t&& event_init = {});
    MAKE_PIMPL(text_format_update_event);
    MAKE_V8_AVAILABLE(WINDOW);

private js_methods:
    auto get_text_formats() -> ranges::any_helpful_view<text_format*>;
};
