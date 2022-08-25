#ifndef SBROWSER2_NAVIGATOR_HPP
#define SBROWSER2_NAVIGATOR_HPP

#include "battery/battery_manager.hpp"
#include "dom_object.hpp"
#include "badging/mixins/navigator_badge.hpp"
#include "device_memory/mixins/navigator_device_memory.hpp"
#include "storage/mixins/navigator_storage.hpp"
namespace html::other {class navigator;}

#include "ext/map.hpp"
#include "ext/optional.hpp"
#include <future>
#include USE_INNER_TYPES(fetch)
#include USE_INNER_TYPES(autoplay)
#include USE_INNER_TYPES(vibration)
namespace battery {class battery_manager;}
namespace dom::other {class dom_exception;}
namespace clipboard {class clipboard;}
namespace gamepad {class gamepad;}
namespace html::elements {class html_media_element;}
namespace media::capabilities {class media_capabilities;}
namespace mediacapture::main {class media_devices;}
namespace mediacapture::main {class media_stream;}
namespace permissions {class permission;}
namespace service_workers::workers {class service_worker_container;}


class html::other::navigator
        : public virtual dom_object
        , public badging::mixins::navigator_badge
        , public device_memory::mixins::navigator_device_memory
        , public storage::mixins::navigator_storage
{
private aliases:
    using navigator_user_media_success_callback = ext::function<void(mediacapture::main::media_stream*)>;
    using navigator_user_media_error_callback   = ext::function<void(dom::other::dom_exception*)>;

public constructors:
    ~navigator() override;

public js_methods:
    /* MEDIACAPTURE_MAIN */
    auto get_user_media(
            ext::map<ext::string, ext::any>&& constraints,
            navigator_user_media_success_callback&& success_callback,
            navigator_user_media_error_callback&& error_callback)
            const -> void;

    /* AUTOPLAY */
    auto get_autoplay_policy(autoplay::detail::autoplay_policy_media_type_t type);
    auto get_autoplay_policy(elements::html_media_element* element);
    auto get_autoplay_policy(webaudio::contexts::audo_context* context);

    /* VIBRATION */
    auto vibrate(vibration::detail::vibrate_pattern_t&& pattern) -> ext::boolean;

    /* BEACON */
    auto send_beacon(ext::string&& url, fetch::detail::body_init_t data = nullptr) -> void;

    /* BADGING */
    auto set_client_badge(ext::optional<ext::number<ulonglong>> contents) -> std::promise<void>;
    auto clear_client_badge() -> std::promise<void>;

    /* BATTERY */
    auto get_battery() -> std::promise<battery::battery_manager*>&;

    /* GAMEPAD */
    auto get_gamepads() -> ext::vector<gamepad::gamepad*>&;

public js_properties:
    /* MEDIACAPTURE_MAIN */
    ext::property<std::unique_ptr<mediacapture::main::media_devices>> media_devices;

    /* PERMISSIONS */
    ext::property<std::unique_ptr<permissions::permission>> permissions;

    /* POINTER_EVENTS */
    ext::property<ext::number<long>> max_touch_points;

    /* CLIPBOARD */
    ext::property<std::unique_ptr<clipboard::clipboard>> clipboard;

    /* MEDIA_CAPABILITIES */
    ext::property<std::unique_ptr<media::capabilities::media_capabilities>> media_capabilities;

    /* SERVICE_WORKERS */
    ext::property<std::unique_ptr<service_workers::workers::service_worker_container>> service_worker;

private js_slots:
    /* BATTERY */
    ext::slot<std::promise<battery::battery_manager*>> s_battery_promise;
    ext::slot<battery::battery_manager*> s_battery_manager;

    /* GAMEPAD */
    ext::slot<ext::boolean> s_has_gamepad;
    ext::slot<ext::vector<gamepad::gamepad*>> s_gamepads;
};

#endif //SBROWSER2_NAVIGATOR_HPP
