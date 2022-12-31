module;
#include "ext/macros.hpp"


export module apis.event_timing.event_counts:p;
import apis.dom_object;
import ext.mixins;


DEFINE_PRIVATE_CLASS(event_timing, event_counts)
        : virtual dom_object_private
        , ext::map_like_linked_private<ext::string, ext::number<ulonglong>>
{
public:
    MAKE_QIMPL(event_counts);
};
