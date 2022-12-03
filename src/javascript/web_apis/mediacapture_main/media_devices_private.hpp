#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_MAIN_MEDIA_DEVICES_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_MAIN_MEDIA_DEVICES_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom/nodes/event_target_private.hpp"

namespace mediacapture::main {class media_device_info;}


DEFINE_PRIVATE_CLASS(mediacapture::main, media_devices) : dom::nodes::event_target_private
{
    ext::map<ext::string, media_device_info*> device_live_map;
    ext::map<ext::string, media_device_info*> device_accessible_map;
    ext::map<ext::string, media_device_info*> kinds_accessible_map;
    ext::vector<media_device_info*> stored_device_list;
    ext::boolean can_expose_camera_info;
    ext::boolean can_expose_microphone_info;
    ext::vector<ext::any> media_stream_track_sources;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_MAIN_MEDIA_DEVICES_PRIVATE_HPP
