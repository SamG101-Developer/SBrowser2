#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EVENT_TIMING_INTERACTION_COUNTS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EVENT_TIMING_INTERACTION_COUNTS_HPP


#include "ext/map_like.ixx"
namespace event_timing {class interaction_counts;}
namespace event_timing {class interaction_counts_private;}


class event_timing::interaction_counts
        : public virtual dom_object
        , public ext::map_like_linked<ext::string, ext::number<ulonglong>>
{
public constructors:
    interaction_counts();
    MAKE_PIMPL(interaction_counts);
    MAKE_V8_AVAILABLE(WINDOW);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EVENT_TIMING_INTERACTION_COUNTS_HPP
