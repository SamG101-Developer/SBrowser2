module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "javascript/macros/expose.hpp"


export module apis.event_timing.interaction_counts;
import apis.dom_object;
import ext.map_like;

import ext.number;
import ext.string;
import ext.tuple;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(event_timing, interaction_counts) final
        : public virtual dom_object
        , public ext::map_like_linked<ext::string, ext::number<ulonglong>>
{
public constructors:
    event_counts();
    MAKE_PIMPL(event_counts);
    MAKE_V8_AVAILABLE(WINDOW);
};
