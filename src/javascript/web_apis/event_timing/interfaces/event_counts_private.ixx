module;
#include "ext/macros/macros.hpp"


export module apis.event_timing.event_counts_private;
import apis.dom_object_private;
import ext.mixins;

import ext.core;


DEFINE_PRIVATE_CLASS(event_timing, event_counts)
        : virtual dom_object_private
        , ext::map_like_linked_private<ext::string, ext::number<ulonglong>>
{
public:
    MAKE_QIMPL(event_counts);
};
