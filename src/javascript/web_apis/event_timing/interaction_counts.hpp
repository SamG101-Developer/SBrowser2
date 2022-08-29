#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EVENT_TIMING_INTERACTION_COUNTS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EVENT_TIMING_INTERACTION_COUNTS_HPP

#include "dom_object.hpp"
#include "ext/map_like.hpp"
namespace event_timing {class interaction_counts;}


class event_timing::interaction_counts
        : public virtual dom_object
        , public ext::map_like_linked<ext::string, ext::number<ulonglong>>
{
public constructors:
    DOM_CTORS(interaction_counts);
    interaction_counts() = default;
};



#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EVENT_TIMING_INTERACTION_COUNTS_HPP