#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_REMOTE_PLAYBACK_REMOTE_PLAYBACK_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_REMOTE_PLAYBACK_REMOTE_PLAYBACK_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom/nodes/event_target_private.hpp"

#include INCLUDE_INNER_TYPES(remote_playback)
#include "ext/number.ixx"
#include "ext/set.hpp"
#include "ext/tuple.ixx"


DEFINE_PRIVATE_CLASS(remote_playback, remote_playback) : dom::nodes::event_target_private
{
    ext::set<ext::tuple<ext::number<long>, detail::remote_playback_availability_callback>> availability_callbacks;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_REMOTE_PLAYBACK_REMOTE_PLAYBACK_PRIVATE_HPP
