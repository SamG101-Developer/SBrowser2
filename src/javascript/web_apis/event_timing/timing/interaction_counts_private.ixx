module;
#include "ext/macros/pimpl.hpp"


export module apis.event_timing.interaction_counts_private;
import apis._.dom_object_private;
import ext.map_like;

import ext.number;
import ext.string;


DEFINE_PRIVATE_CLASS(event_timing, interaction_counts)
        : virtual dom_object_private
        , ext::map_like_linked_private<ext::string, ext::number<ulonglong>>
{
public:
    MAKE_QIMPL(event_counts);
};
