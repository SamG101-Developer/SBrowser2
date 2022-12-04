#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_NOTIFICATIONS_DETAIL_NOTIFICATION_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_NOTIFICATIONS_DETAIL_NOTIFICATION_INTERNALS_HPP


#include "ext/optional.ixx"
#include "ext/string.hpp"

#include INCLUDE_INNER_TYPES(hr_time)
#include INCLUDE_INNER_TYPES(notifications)
#include INCLUDE_INNER_TYPES(permissions)
#include INCLUDE_INNER_TYPES(service_workers)
#include INCLUDE_INNER_TYPES(vibration)
#include INCLUDE_INNER_TYPES(url)


namespace notifications::detail
{
    auto is_non_persistent_notification(
            const notification_t&)
            -> ext::boolean;

    auto is_persistent_notification(
            const notification_t&)
            -> ext::boolean;

    auto create_notification(
            ext::string&& title,
            notification_options_t&& options,
            v8::Local<v8::Object> environment_settings,
            ext::optional<service_workers::detail::service_worker_registration_t&> = ext::nullopt)
            -> notification_t;

    auto get_notifications_permission_state()
            -> permissions::detail::permission_state_t;

    auto fetch_steps(
            const notification_t& notification)
            -> void;

    auto show_steps(
            const notification_t& notification)
            -> void;

    auto activate_notification(
            const notification_t& notification)
            -> void;

    auto close_notification(
            const notification_t& notification)
            -> void;

    auto alert_steps(
            const notification_t& notification)
            -> void;
}


struct notifications::detail::action_t
{
    ext::string title;
    ext::string name;

    ext::pair<url::detail::url_t, icon_resource_t*> icon_url;
};

struct notifications::detail::notification_t
{
    service_workers::detail::service_worker_registration_t& service_worker_registration;
    ext::string title;
    ext::string body;
    ext::string language;
    ext::string tag;
    notification_direction_t direction;

    ext::any data;
    hr_time::epoch_time_stamp time_stamp;
    ext::string origin;

    ext::boolean renotify_preference = false;
    ext::boolean silent_preference = false;
    ext::boolean require_interaction_preference = false;

    ext::pair<url::detail::url_t, image_resource_t*> image_url;
    ext::pair<url::detail::url_t, icon_resource_t*> icon_url;
    ext::pair<url::detail::url_t, badge_resource_t*> badge_url;

    vibration::detail::vibrate_pattern_t vibration_pattern;
    ext::vector<action_t*> actions;
};

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_NOTIFICATIONS_DETAIL_NOTIFICATION_INTERNALS_HPP
