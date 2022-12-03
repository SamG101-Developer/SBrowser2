#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_NOTIFICATIONS__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_NOTIFICATIONS__TYPEDEFS_HPP


#include "ext/map.ixx"
#include "ext/string.hpp"

namespace notifications::detail
{
    struct notification_t;
    struct image_resource_t;
    struct icon_resource_t;
    struct badge_resource_t;
    struct action_t;

    enum class notification_permission_t {DEFAULT, DENIED, GRANTED};
    enum class notification_direction_t {AUTO, LTR, RTL};

    using notification_options_t = ext::map<ext::string, ext::any>;
    using notification_action_t = ext::map<ext::string, ext::any>;
    using notification_permission_callback = std::function<void(notification_permission_t)>;
    using get_notification_options_t = ext::map<ext::string, ext::any>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_NOTIFICATIONS__TYPEDEFS_HPP
