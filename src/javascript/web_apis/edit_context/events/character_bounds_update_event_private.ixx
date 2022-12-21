module;
#include "ext/macros/pimpl.hpp"


export module apis.edit_context.character_bounds_update_event_private;
import apis.dom.event_private;

import ext.core;


DEFINE_PRIVATE_CLASS(edit_context::events, character_bounds_update_event)
        : dom::event_private
{
    MAKE_QIMPL(character_bounds_update_event);
    ext::number<ulong> range_start;
    ext::number<ulong> range_end;
};
