#include "devices_internals.hpp"




#include "ext/set.hpp"



#include "ext/vector.hpp"

#include "javascript/environment/realms_2.hpp"





#include "html/detail/document_internals.hpp"

#include "mediacapture_main/detail/source_internals.hpp"
#include "mediacapture_main/media_device_info.hpp"
#include "mediacapture_main/media_devices.hpp"
#include "mediacapture_main/media_stream.hpp"
#include "mediacapture_main/media_stream_track.hpp"

#include "permissions/detail/permission_internals.hpp"

#include <range/v3/action/remove_if.hpp>
#include <range/v3/view/concat.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/take.hpp>
#include <range/v3/to_container.hpp>
#include <v8-object.h>
#include <v8pp/convert.hpp>


auto mediacapture::detail::on_page_load(
        main::media_devices* media_devices)
        -> void
{
    JS_BLOCK_ENTER
        JS_REALM_GET_RELEVANT(media_devices)

        // set 7 slot values of the relevant global object, that hold information about permissions and device exposure,
        // primarily concerning the access the web page has to the camera and microphone devices. all the slots are
        // given default values

        js::env::realms::set(
                media_devices_relevant_global_object, "[[devices_live_map]]",
                ext::map<ext::string, ext::boolean>{});

        js::env::realms::set(
                media_devices_relevant_global_object, "[[devices_accessible_map]]",
                ext::map<ext::string, ext::boolean>{});

        js::env::realms::set(
                media_devices_relevant_global_object, "[[kinds_accessible_map]]",
                ext::map<ext::string, ext::boolean>{});

        js::env::realms::set(
                media_devices_relevant_global_object, "[[stored_device_list]]",
                ext::vector<main::media_devices*>{});

        js::env::realms::set(
                media_devices_relevant_global_object, "[[can_expose_camera_info]]",
                ext::boolean::FALSE_());

        js::env::realms::set(
                media_devices_relevant_global_object, "[[can_expose_microphone_info]]",
                ext::boolean::FALSE_());

        js::env::realms::set(
                media_devices_relevant_global_object, "[[media_stream_track_sources]]",
                ext::set<media_stream_track_source_t*>{});


        using permissions::detail::powerful_feature_t;
        using permissions::detail::permissions_descriptor_t;
        using permissions::detail::permission_state_t;

        // TODO : this is wrong (should be MediaDeviceInfo somewhere)
        ext::vector<main::media_device_info*> devices; // TODO : where are the devices stored?
        auto devices_live_map = js::env::realms::get<ext::map<ext::string, ext::boolean>>(media_devices_relevant_global_object, "[[devices_live_map]]");
        auto kinds_accessible_map = js::env::realms::get<ext::map<ext::string, ext::boolean>>(media_devices_relevant_global_object, "[[kinds_accessible_map]]");
        auto devices_accessible_map = js::env::realms::get<ext::map<ext::string, ext::boolean>>(media_devices_relevant_global_object, "[[devices_accessible_map]]");

        // iterate through each device
        for (auto* device: devices)
        {
            auto kind = device->kind();

            // convert the kind of device to the permission name, and create a powerful feature object from it, setting
            // the name to the 'permission_name'. create a permissions descriptor from the powerful feature, and
            // determine the state of this 'permission_descriptor'
            auto permission_name = kind == media_device_kind_t::VIDEO_INPUT ? "camera" : kind == media_device_kind_t::AUDIO_INPUT ? "microphone" : "";
            powerful_feature_t powerful_feature {.name = permission_name};
            permissions_descriptor_t permissions_descriptor{{"name", std::move(powerful_feature)}};
            auto permission_state = permissions::detail::permission_state(
                    std::move(permissions_descriptor),
                    media_devices_relevant_global_object);

            // emplace values into the slots on the relevant global object
            kinds_accessible_map.emplace(std::move(kind), permission_state == permission_state_t::GRANTED);
            devices_live_map.emplace(device->device_id(), ext::boolean::FALSE_());
            devices_accessible_map.emplace(device->device_id(), permission_state == permission_state_t::GRANTED);
        }

    JS_BLOCK_EXIT

    // TODO : transition of permission state
}


auto mediacapture::detail::device_change_notification_steps()
        -> void
{
    JS_REALM_GET_RELEVANT(nullptr);

    // get the associated document of the relevant global objectm the current devices stored by this document, and all
    // of available devices that can be stored by a document
    auto* associated_document = js::env::realms::get<dom::nodes::document*>(nullptr_relevant_global_object, "associated_document");
    auto stored_device_list = js::env::realms::get<ext::vector<main::media_devices*>>(nullptr_relevant_global_object, "[[stored_device_list]]");
    auto device_list = all_available_devices();

    // convert the 2 device lists into MediaDeviceInfo lists
    auto last_exposed_devices = create_list_of_device_info_objects(stored_device_list, associated_document);
    auto new_exposed_devices = create_list_of_device_info_objects(device_list, associated_document);

    // if the 2 lists are the same, then the devices haven't changed, so abort these steps as creating a notification
    // for this in unnecessary; nothing has mutated
    return_if (new_exposed_devices == last_exposed_devices);

    // set the [[stored_device_list]] slot in the relevant global object to the new device list that was created
    js::env::realms::set(nullptr_relevant_global_object, "[[stored_device_list]]", std::move(device_list));

    // fire a "devicechange" event at each device
    for (auto* device: device_list)
        dom::detail::queue_microtask(
                [device] mutable
                {dom::detail::fire_event("devicechange", device);});
}


auto mediacapture::detail::create_list_of_device_info_objects(
        ext::vector_view<main::media_devices*> device_list,
        dom::nodes::document* document)
        -> ext::vector<main::media_device_info*>
{
    using result_list_t = ext::vector<main::media_device_info*>;
    // TODO : sort the 'microphone_list' and 'camera_list' to have the system default devices at the front

    // the 'microphone_list' is the 'device_list', but filtered for microphone devices, and then transformed into the
    // MediaDeviceInfo that represents the MediaDevices object. if the Document isn't allowed to use the microphone
    // feature, then this is skipped, and the' microphone_list' is empty
    auto microphone_list = html::detail::allowed_to_use(document, "microphone") ? device_list
            | ranges::views::filter(is_microphone)
            | ranges::views::transform(create_device_info_object)
            : ranges::any_view<main::media_device_info*>{};

    // the 'camera_list' is the 'device_list', but filtered for camera devices, and then transformed into the
    // MediaDeviceInfo that represents the MediaDevices object. if the Document isn't allowed to use the camera feature,
    // then this is skipped, and the 'camera_list' is empty
    auto camera_list = html::detail::allowed_to_use(document, "camera") ? device_list
            | ranges::views::filter(is_camera)
            | ranges::views::transform(create_device_info_object)
            : ranges::any_view<main::media_device_info*>{};

    // if the devices information can not be exposed, then take the system microphone and camera from the devices list
    // by filtering them and taking the first item TODO : what happens if list is empty?
    if (!device_information_can_be_exposed())
    {
        microphone_list = std::move(microphone_list)
                | ranges::views::filter(is_system_default_microphone)
                | ranges::views::take(1);

        camera_list = std::move(camera_list)
                | ranges::views::filter(is_system_default_camera)
                | ranges::views::take(1);;
    }

    // the 'other_device_list' is the 'device_list', but filtered for non-camera and -microphone devices, and then
    // transformed into the MediaDeviceInfo that represents the MediaDevices object. any MediaDevices that is not
    // allowed to be exposed, with respect to the 'camera_list' and 'microphone_list' is removed. they then transformed
    // into the MediaDeviceInfo that represents the MediaDevices object
    auto other_device_list = device_list
            | ranges::views::remove_if(is_camera)
            | ranges::views::remove_if(is_microphone)
            | ranges::views::remove_if(ext::bind_back{other_information_can_be_exposed, microphone_list, camera_list})
            | ranges::views::transform(create_device_info_object);

    // return a concatenation of the 'microphone_list', 'camera_list', and the 'other_devices_list', converted to a
    // vector type
    return ranges::views::concat(microphone_list, camera_list, other_device_list) | ranges::to<result_list_t>;
}


auto mediacapture::detail::create_device_info_object(
        main::media_devices* device)
        -> main::media_device_info
{
    main::media_device_info device_info;
    // TODO set device_info.[kind, label]

    return_if(device_info.kind() == media_device_kind_t::VIDEO_INPUT && !camera_information_can_be_exposed()) device_info;
    return_if(device_info.kind() == media_device_kind_t::AUDIO_INPUT && !microphone_information_can_be_exposed()) device_info;

    // TODO : deviceId, groupId
    return device_info;
}


auto mediacapture::detail::device_enumeration_can_proceed()
        -> ext::boolean
{
    // if the device information can be exposed, then enumeration can proceed, as the information is allowed to be used
    return_if(device_information_can_be_exposed()) ext::boolean::TRUE_();

    // otherwise, check if the relevant global object's associated document (Document) is fully active, and has focus.
    // if both of these conditions are met, then the devices enumeration can proceed
    JS_REALM_GET_RELEVANT(nullptr);
    auto* associated_document = js::env::realms::get<dom::nodes::document*>(nullptr_relevant_global_object, "associated_document");
    return dom::detail::is_document_fully_active(associated_document); // TODO : && must have focus
}


auto mediacapture::detail::device_information_can_be_exposed()
        -> ext::boolean
{
    // a device's information can be exposed if the camera or microphone information can be exposed
    return camera_information_can_be_exposed() || microphone_information_can_be_exposed();
}


auto mediacapture::detail::other_information_can_be_exposed(
        main::media_devices* device,
        ext::vector_view<main::media_devices*> microphone_list,
        ext::vector_view<main::media_devices*> camera_list)
        -> ext::boolean
{
    /* MEDIACAPTURE_OUTPUT */
    // TODO: https://w3c.github.io/mediacapture-output/#privacy-obtaining-consent
}


auto mediacapture::detail::set_device_information_exposure(
        ext::set<ext::string>&& requested_types,
        ext::boolean value)
        -> void
{
    JS_REALM_GET_RELEVANT(nullptr);

    // if any of the requested types contains "video", then set the [[can_expose_camera_info]] slot of the relevant
    // global object to the value parameter
    if (ranges::contains(std::move(requested_types), "video"))
        js::env::realms::set(
                nullptr_relevant_global_object, "[[can_expose_camera_info]]",
                std::move(value));

    // if any of the requested types contains "microphone", then set the [[can_expose_camera_info]] slot of the relevant
    // global object to the value parameter
    if (ranges::contains(std::move(requested_types), "audio"))
        js::env::realms::set(
                nullptr_relevant_global_object, "[[can_expose_microphone_info]]",
                std::move(value));
}
