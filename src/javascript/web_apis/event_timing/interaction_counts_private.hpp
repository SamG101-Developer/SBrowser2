#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EVENT_TIMING_INTERACTION_COUNTS_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EVENT_TIMING_INTERACTION_COUNTS_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "ext/map_like.hpp"
#include "dom_object_private.hpp"


DEFINE_PRIVATE_CLASS(event_timing, interaction_counts)
        : virtual dom_object_private
        , ext::map_like_linked_private<ext::string, ext::number<ulonglong>>
{};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EVENT_TIMING_INTERACTION_COUNTS_PRIVATE_HPP
