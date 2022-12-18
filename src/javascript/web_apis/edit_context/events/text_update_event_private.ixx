module;
#include "ext/macros/pimpl.hpp"


export module apis.edit_context.text_update_event_private;
import apis.dom.event_private;

import ext.number;
import ext.string;


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
