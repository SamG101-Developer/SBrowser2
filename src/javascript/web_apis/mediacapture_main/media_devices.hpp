#pragma once
#ifndef SBROWSER2_MEDIA_DEVICES_HPP
#define SBROWSER2_MEDIA_DEVICES_HPP

#include "dom/nodes/event_target.hpp"
namespace mediacapture::main {class media_devices;}

#include "ext/any.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"
#include <future>
namespace mediacapture::main {class media_device_info;}
namespace mediacapture::main {class media_stream;}


class mediacapture::main::media_devices
        : public dom::nodes::event_target
{
public js_methods:
    auto enumerate_devices() -> std::promise<ext::vector<media_device_info*>>;
    auto get_user_media(ext::map<ext::string, ext::any>&& constraints = {}) -> std::promise<media_stream*>;
    auto get_supported_constraints() -> ext::map<ext::string, ext::any>;
};


#endif //SBROWSER2_MEDIA_DEVICES_HPP
