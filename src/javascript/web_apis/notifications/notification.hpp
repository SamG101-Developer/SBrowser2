#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_NOTIFICATIONS_NOTIFICATION_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_NOTIFICATIONS_NOTIFICATION_HPP

#include "dom/nodes/event_target.hpp"
namespace notifications {class notification;}

#include "ext/type_traits.hpp"
#include INCLUDE_INNER_TYPES(hr_time)
#include INCLUDE_INNER_TYPES(notifications)


class notifications::notification
        : public dom::nodes::event_target
{
public constructors:
    DOM_CTORS(notification);
    notification() = default;
    notification(ext::string&& title, detail::notification_options_t&& options = {});

public js_methods:
    auto close() -> void;

private js_properties:
    static ext::property<ext::number<ulong>> max_actions;
    ext::property<ext::string> title;
    ext::property<ext::string> lang;
    ext::property<ext::string> body;
    ext::property<ext::string> tag;
    ext::property<ext::string> icon;
    ext::property<ext::string> badge;
    ext::property<detail::notification_direction_t> dir;
    ext::property<hr_time::epoch_time_stamp> time_stamp;
    ext::property<ext::boolean> renotify;
    ext::property<ext::boolean> silent;
    ext::property<ext::boolean> require_interaction;
    ext::property<ext::any> data;
    ext::property<std::unique_ptr<const ext::vector<ext::number<ulong>>>> vibrates;
    ext::property<std::unique_ptr<const ext::vector<detail::notification_action_t*>>> actions;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_NOTIFICATIONS_NOTIFICATION_HPP
