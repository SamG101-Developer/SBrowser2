module;
#include "ext/macros.hpp"


export module apis.edit_context.text_update_event:p;
import apis.dom.event;


DEFINE_PRIVATE_CLASS(edit_context, text_update_event)
        : dom::event_private
{
public:
    MAKE_QIMPL(text_update_event);

public:
    ext::number<ulong> update_range_start;
    ext::number<ulong> update_range_end;
    ext::number<ulong> selection_start;
    ext::number<ulong> selection_end;
    ext::number<ulong> composition_start;
    ext::number<ulong> composition_end;
    ext::string text;
};
