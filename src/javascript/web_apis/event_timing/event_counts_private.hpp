#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EVENT_TIMING_EVENT_COUNTS_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EVENT_TIMING_EVENT_COUNTS_PRIVATE_HPP

#include "ext/pimpl.ixx"


#include "ext/map_like.ixx"


DEFINE_PRIVATE_CLASS(event_timing, event_counts)
        : virtual dom_object_private
        , ext::map_like_linked_private<ext::string, ext::number<ulonglong>>
{
    MAKE_QIMPL(event_counts);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EVENT_TIMING_EVENT_COUNTS_PRIVATE_HPP
