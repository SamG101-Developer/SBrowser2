#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SCREEN_WAKE_LOCK_WAKE_LOCK_SENTINEL_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SCREEN_WAKE_LOCK_WAKE_LOCK_SENTINEL_PRIVATE_HPP

#include "ext/pimpl.ixx"


#include INCLUDE_INNER_TYPES(screen_wake_lock)


DEFINE_PRIVATE_CLASS(screen_wake_lock, wake_lock_sentinel) : dom::nodes::event_target_private
{
    ext::boolean released;
    detail::wake_lock_type type;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SCREEN_WAKE_LOCK_WAKE_LOCK_SENTINEL_PRIVATE_HPP
