#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EVENT_TIMING_EVENT_COUNTS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EVENT_TIMING_EVENT_COUNTS_HPP

#include "dom_object.hpp"
#include "ext/map_like.hpp"
namespace event_timing {class event_counts;}
namespace event_timing {class event_counts_private;}


class event_timing::event_counts
        : public virtual dom_object
        , public ext::map_like_linked<ext::string, ext::number<ulonglong>>
{
public constructors:
    event_counts();
    MAKE_PIMPL(event_counts);
    MAKE_V8_AVAILABLE(WINDOW);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EVENT_TIMING_EVENT_COUNTS_HPP
