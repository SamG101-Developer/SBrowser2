module;
#include "ext/macros.hpp"


export module apis.edit_context.text_format_update_event:p;
import apis.dom.event;

IMPORT_ALL_TYPES(edit_context);


DEFINE_PRIVATE_CLASS(edit_context, text_format_update_event)
        : dom::event_private
{
public:
    MAKE_QIMPL(text_format_update_event);

public:
    ext::vector<std::unique_ptr<text_format>> text_formats;
};
