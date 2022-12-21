module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.edit_context.character_bounds_update_event;
import apis.dom.event;

import ext.core;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(edit_context, character_bounds_update_event) final
        : public dom::event
{
public typedefs:
    using character_bounds_update_event_init_t = ext::map<ext::string, ext::any>;

public constructors:
    character_bounds_update_event(ext::string&& event_type, character_bounds_update_event_init_t&& event_init = {});
    MAKE_PIMPL(character_bounds_update_event);
    MAKE_V8_AVAILABLE(WINDOW);

private js_properties:
    DEFINE_GETTER(range_start, ext::number<ulong>);
    DEFINE_GETTER(range_end, ext::number<ulong>);
};
