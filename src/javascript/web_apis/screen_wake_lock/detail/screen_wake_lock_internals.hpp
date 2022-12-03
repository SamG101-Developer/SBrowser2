#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SCREEN_WAKE_LOCK_DETAIL_SCREEN_WAKE_LOCK_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SCREEN_WAKE_LOCK_DETAIL_SCREEN_WAKE_LOCK_INTERNALS_HPP

#include "ext/keywords.ixx"
#include INCLUDE_INNER_TYPES(screen_wake_lock)

namespace dom::nodes {class document;}
namespace screen_wake_lock {class wake_lock_sentinel;}


namespace screen_wake_lock::detail
{
    auto aquire_wake_lock(
            wake_lock_type type)
            -> void;

    auto release_wake_lock(
            wake_lock_type type,
            dom::nodes::document* document,
            wake_lock_sentinel* lock)
            -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SCREEN_WAKE_LOCK_DETAIL_SCREEN_WAKE_LOCK_INTERNALS_HPP
