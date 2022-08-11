#pragma once
#ifndef SBROWSER2_INPUT_DEVICE_INFO_HPP
#define SBROWSER2_INPUT_DEVICE_INFO_HPP

#include "mediacapture_main/media_device_info.hpp"
namespace mediacapture::main {class input_device_info;}

#include "ext/map.hpp"


class mediacapture::main::input_device_info
        : public media_device_info
{
public js_methods:
    auto get_capabilities() const -> ext::map<ext::string, ext::any>;
};


#endif //SBROWSER2_INPUT_DEVICE_INFO_HPP