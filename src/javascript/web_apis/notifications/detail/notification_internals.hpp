#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_NOTIFICATIONS_DETAIL_NOTIFICATION_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_NOTIFICATIONS_DETAIL_NOTIFICATION_INTERNALS_HPP

#include "ext/pair.hpp"
#include "ext/optional.hpp"
#include "ext/string.hpp"
#include "url/url.hpp"
#include USE_INNER_TYPES(high_resolution_time)
#include USE_INNER_TYPES(notifications)
#include USE_INNER_TYPES(permissions)
#include USE_INNER_TYPES(service_workers)
#include USE_INNER_TYPES(vibration)


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

    ext::pair<url::url_object, icon_resource_t*> icon_url;
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
    high_resolution_time::detail::epoch_time_stamp_t time_stamp;
    ext::string origin;

    ext::boolean renotify_preference = false;
    ext::boolean silent_preference = false;
    ext::boolean require_interaction_preference = false;

    ext::pair<url::url_object, image_resource_t*> image_url;
    ext::pair<url::url_object, icon_resource_t*> icon_url;
    ext::pair<url::url_object, badge_resource_t*> badge_url;

    vibration::detail::vibrate_pattern_t vibration_pattern;
    ext::vector<action_t*> actions;
};

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_NOTIFICATIONS_DETAIL_NOTIFICATION_INTERNALS_HPP