#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_OTHER_NAVIGATOR_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_OTHER_NAVIGATOR_PRIVATE_HPP

#include "ext/pimpl.ixx"

#include "html/navigators/mixins/navigator_id_private.hpp"
#include "html/navigators/mixins/navigator_language_private.hpp"
#include "html/navigators/mixins/navigator_on_line_private.hpp"
#include "html/navigators/mixins/navigator_content_utils_private.hpp"
#include "html/navigators/mixins/navigator_cookies_private.hpp"
#include "html/navigators/mixins/navigator_plugins_private.hpp"
#include "html/navigators/mixins/navigator_concurrent_hardware_private.hpp"
#include "badging/mixins/navigator_badge_private.hpp"
#include "device_memory/mixins/navigator_device_memory_private.hpp"
#include "storage/mixins/navigator_storage_private.hpp"
#include "web_locks/mixins/navigator_locks_private.hpp"


#include "ext/vector.hpp"
namespace battery {class battery_manager;}
namespace gamepad {class gamepad;}
namespace mediasession {class media_session;}


DEFINE_PRIVATE_CLASS(html::navigators, navigator)
        : virtual dom_object_private
        , public html::navigators::mixins::navigator_id_private
        , public html::navigators::mixins::navigator_language_private
        , public html::navigators::mixins::navigator_on_line_private
        , public html::navigators::mixins::navigator_content_utils_private
        , public html::navigators::mixins::navigator_cookies_private
        , public html::navigators::mixins::navigator_plugins_private
        , public html::navigators::mixins::navigator_concurrent_hardware_private

        , public badging::mixins::navigator_badge_private
        , public device_memory::mixins::navigator_device_memory_private
        , public storage::mixins::navigator_storage_private
        , public web_locks::mixins::navigator_locks_private
{
    /* [BATTERY] */
    ext::promise<battery::battery_manager*> battery_promise;
    std::unique_ptr<battery::battery_manager> battery_manager;

    /* [GAMEPAD] */
    ext::boolean has_gamepad_gesture;
    ext::vector<gamepad::gamepad*> gamepads;

    /* [Permissions] */
    std::unique_ptr<permissions::permissions> permissions;

    /* [MEDIASESSION] */
    std::unique_ptr<mediasession::media_session> media_session;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_OTHER_NAVIGATOR_PRIVATE_HPP
