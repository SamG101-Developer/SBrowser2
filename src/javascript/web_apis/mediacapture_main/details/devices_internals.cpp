#include "devices_internals.hpp"

#include "ext/boolean.hpp"
#include "ext/map.hpp"
#include "ext/set.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"

#include "javascript/environment/realms_2.hpp"

#include "mediacapture_main/details/source_internals.hpp"
#include "mediacapture_main/media_devices.hpp"
#include "mediacapture_main/media_stream_track.hpp"

#include <v8-object.h>
#include <v8pp/convert.hpp>


auto mediacapture::detail::devices_internals::on_page_load(
        main::media_devices* media_devices)
        -> void
{
    JS_BLOCK_ENTER
        JS_REALM_GET_RELEVANT(media_devices)

        media_devices_relevant_global_object->SetPrivate(
                media_devices_relevant_realm,
                v8pp::to_v8(media_devices_relevant_agent, "[[devices_live_map]]").As<v8::Private>(),
                v8pp::to_v8(media_devices_relevant_agent, ext::map<ext::string, main::media_devices*>{}));

        media_devices_relevant_global_object->SetPrivate(
                media_devices_relevant_realm,
                v8pp::to_v8(media_devices_relevant_agent, "[[devices_accessible_map]]").As<v8::Private>(),
                v8pp::to_v8(media_devices_relevant_agent, ext::map<ext::string, ext::boolean*>{}));

        media_devices_relevant_global_object->SetPrivate(
                media_devices_relevant_realm,
                v8pp::to_v8(media_devices_relevant_agent, "[[kinds_accessible_map]]").As<v8::Private>(),
                v8pp::to_v8(media_devices_relevant_agent, ext::map<ext::string, ext::boolean>{}));

        media_devices_relevant_global_object->SetPrivate(
                media_devices_relevant_realm,
                v8pp::to_v8(media_devices_relevant_agent, "[[stored_device_list]]").As<v8::Private>(),
                v8pp::to_v8(media_devices_relevant_agent, ext::vector<main::media_devices*>{}));

        media_devices_relevant_global_object->SetPrivate(
                media_devices_relevant_realm,
                v8pp::to_v8(media_devices_relevant_agent, "[[can_expose_camera_info]]").As<v8::Private>(),
                v8pp::to_v8(media_devices_relevant_agent, ext::boolean::FALSE_()));

        media_devices_relevant_global_object->SetPrivate(
                media_devices_relevant_realm,
                v8pp::to_v8(media_devices_relevant_agent, "[[can_expose_microphone_info]]").As<v8::Private>(),
                v8pp::to_v8(media_devices_relevant_agent, ext::boolean::FALSE_()));

        media_devices_relevant_global_object->SetPrivate(
                media_devices_relevant_realm,
                v8pp::to_v8(media_devices_relevant_agent, "[[media_stream_track_sources]]").As<v8::Private>(),
                v8pp::to_v8(media_devices_relevant_agent, ext::set<source_internals::media_stream_track_source*>{}));

    JS_BLOCK_EXIT

    for (auto& device: media_devices->get_user_media())
}
