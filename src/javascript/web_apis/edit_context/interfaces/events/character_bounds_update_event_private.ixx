module;
#include "ext/macros.hpp"


export module apis.edit_context.character_bounds_update_event:p;
import apis.dom.event;


DEFINE_PRIVATE_CLASS(edit_context::events, character_bounds_update_event)
        : dom::event_private
{
    MAKE_QIMPL(character_bounds_update_event);
    ext::number<ulong> range_start;
    ext::number<ulong> range_end;
};
