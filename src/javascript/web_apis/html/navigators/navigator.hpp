#ifndef SBROWSER2_NAVIGATOR_HPP
#define SBROWSER2_NAVIGATOR_HPP

#include "dom_object.hpp"
#include "html/navigators/mixins/navigator_id.hpp"
#include "html/navigators/mixins/navigator_language.hpp"
#include "html/navigators/mixins/navigator_on_line.hpp"
#include "html/navigators/mixins/navigator_content_utils.hpp"
#include "html/navigators/mixins/navigator_cookies.hpp"
#include "html/navigators/mixins/navigator_plugins.hpp"
#include "html/navigators/mixins/navigator_concurrent_hardware.hpp"
#include "badging/mixins/navigator_badge.hpp"
#include "device_memory/mixins/navigator_device_memory.hpp"
#include "storage/mixins/navigator_storage.hpp"
namespace html::navigators {class navigator;}
namespace html::navigators {class navigator_private;}

#include "ext/map.hpp"
#include "ext/optional.hpp"
#include "ext/promise.hpp"
#include "ext/span.hpp"
#include INCLUDE_INNER_TYPES(autoplay)
#include INCLUDE_INNER_TYPES(fetch)
#include INCLUDE_INNER_TYPES(autoplay)
#include INCLUDE_INNER_TYPES(vibration)
namespace battery {class battery_manager;}
namespace dom::other {class dom_exception;}
namespace clipboard {class clipboard;}
namespace contact_picker {class contacts_manager;}
namespace device_posture {class device_posture;}
namespace gamepad {class gamepad;}
namespace html::elements {class html_media_element;}
namespace media::capabilities {class media_capabilities;}
namespace mediacapture::main {class media_devices;}
namespace mediacapture::main {class media_stream;}
namespace mediasession {class media_session;}
namespace permissions {class permission;}
namespace service_workers::workers {class service_worker_container;}
namespace webappsec::credential_management {class credentials_container;}


class html::navigators::navigator
        : public virtual dom_object
        , public html::navigators::mixins::navigator_id
        , public html::navigators::mixins::navigator_language
        , public html::navigators::mixins::navigator_on_line
        , public html::navigators::mixins::navigator_content_utils
        , public html::navigators::mixins::navigator_cookies
        , public html::navigators::mixins::navigator_plugins
        , public html::navigators::mixins::navigator_concurrent_hardware

        , public badging::mixins::navigator_badge
        , public device_memory::mixins::navigator_device_memory
        , public storage::mixins::navigator_storage
{
private aliases:
    using navigator_user_media_success_callback_t = ext::function<void(mediacapture::main::media_stream*)>;
    using navigator_user_media_error_callback_t   = ext::function<void(dom::other::dom_exception*)>;

public constructors:
    navigator();
    ~navigator() override;
    MAKE_PIMPL(navigator);
    MAKE_V8_AVAILABLE(SECURE);

public js_methods:
    /* [MEDIACAPTURE-MAIN] */
    auto get_user_media(
            ext::map<ext::string, ext::any>&& constraints,
            navigator_user_media_success_callback_t&& success_callback,
            navigator_user_media_error_callback_t&& error_callback)
            const -> void;

    /* [AUTOPLAY] */
    auto get_autoplay_policy(autoplay::detail::autoplay_policy_media_type_t type) -> autoplay::detail::autoplay_policy_t;
    auto get_autoplay_policy(elements::html_media_element* element) -> autoplay::detail::autoplay_policy_t;
    auto get_autoplay_policy(webaudio::contexts::audio_context* context) -> autoplay::detail::autoplay_policy_t;

    /* [VIBRATION] */
    auto vibrate(vibration::detail::vibrate_pattern_t&& pattern) -> ext::boolean;

    /* [BEACON] */
    auto send_beacon(ext::string&& url, fetch::detail::body_init_t data = nullptr) -> ext::boolean;

    /* [BADGING] */
    auto set_client_badge(ext::optional<ext::number<ulonglong>> contents) -> ext::promise<void>;
    auto clear_client_badge() -> ext::promise<void>;

    /* [BATTERY] */
    auto get_battery() -> ext::promise<battery::battery_manager*>&;

    /* [GAMEPAD] */
    auto get_gamepads() -> ext::vector_span<gamepad::gamepad*>;

private js_properties:
    /* [DEVICE-POSTURE] */
    DEFINE_GETTER(device_posture, device_posture::device_posture*);

    /* [MEDIACAPTURE-MAIN] */
    DEFINE_GETTER(media_devices, mediacapture::main::media_devices*);

    /* [PERMISSIONS] */
    DEFINE_GETTER(permissions, permissions::permission*);

    /* [POINTER-EVENTS] */
    DEFINE_GETTER(max_touch_points, ext::number<long>);

    /* [CLIPBOARD] */
    DEFINE_GETTER(clipboard, clipboard::clipboard);

    /* [MEDIA-CAPABILITIES] */
    DEFINE_GETTER(media_capabilities, media::capabilities::media_capabilities*);

    /* [SERVICE-WORKERS] */
    DEFINE_GETTER(service_worker, service_workers::workers::service_worker_container*);

    /* [CONTACT-PICKER] */
    DEFINE_GETTER(contacts, contact_picker::contacts_manager*);

    /* [WEBAPPSEC-CREDENTIALS-MANAGEMENT] */
    DEFINE_GETTER(credentials, webappsec::credential_management::credentials_container*);

    /* [PRESENTATION] */
    DEFINE_GETTER(presentation, presentation::presentation*);

    /* [SCREN-WAKE-LOCK] */
    DEFINE_GETTER(wake_lock, screen_wake_lock::wake_lock); // TODO : attribute name

    /* [MEDIA_SESSION] */
    DEFINE_GETTER(media_session, mediasession::media_session*);
};

#endif //SBROWSER2_NAVIGATOR_HPP
