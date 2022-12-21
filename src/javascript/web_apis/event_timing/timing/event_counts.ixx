module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "javascript/macros/expose.hpp"


export module apis.event_timing.event_counts;
import apis.dom_object;
import ext.mixins;

import ext.core;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(event_timing, event_counts) final
        : public virtual dom_object
        , public ext::map_like_linked<ext::string, ext::number<ulonglong>>
{
public constructors:
    event_counts();
    MAKE_PIMPL(event_counts);
    MAKE_V8_AVAILABLE(WINDOW);
};
