#pragma once
#ifndef SBROWSER2_DEVICES_INTERNALS_HPP
#define SBROWSER2_DEVICES_INTERNALS_HPP


#include "ext/set.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"
namespace dom::nodes {class document;}
namespace mediacapture::main {class media_devices;}
namespace mediacapture::main {class media_device_info;}

namespace mediacapture::detail
{
    auto on_page_load(
            main::media_devices* media_devices)
            -> void;

    auto device_change_notification_steps()
            -> void; // TODO

    auto all_available_devices()
            -> ext::vector<main::media_devices*>;

    auto is_system_default_microphone(
            main::media_devices* device)
            -> ext::boolean;

    auto is_system_default_camera(
            main::media_devices* device)
            -> ext::boolean;

    auto is_system_default_audio(
            main::media_devices* device)
            -> ext::boolean;

    auto is_microphone(
            main::media_devices* device)
            -> ext::boolean;

    auto is_camera(
            main::media_devices* device)
            -> ext::boolean;

    auto create_list_of_device_info_objects(
            ext::vector_view<main::media_devices*> device_list,
            dom::nodes::document* document)
            -> ext::vector<main::media_device_info*>;

    auto create_device_info_object(
            main::media_devices* device)
            -> main::media_device_info;

    auto device_enumeration_can_proceed()
            -> ext::boolean;

    auto device_information_can_be_exposed()
            -> ext::boolean;

    auto camera_information_can_be_exposed()
            -> ext::boolean;

    auto microphone_information_can_be_exposed()
            -> ext::boolean;

    auto other_information_can_be_exposed(
            main::media_devices* device,
            ext::vector_view<main::media_devices*> microphone_list,
            ext::vector_view<main::media_devices*> camera_list)
            -> ext::boolean;

    auto set_device_information_exposure(
            ext::set<ext::string>&& requested_types,
            ext::boolean value)
            -> void;
};


#endif //SBROWSER2_DEVICES_INTERNALS_HPP
