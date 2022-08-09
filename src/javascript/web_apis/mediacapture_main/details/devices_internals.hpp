#pragma once
#ifndef SBROWSER2_DEVICES_INTERNALS_HPP
#define SBROWSER2_DEVICES_INTERNALS_HPP


namespace mediacapture::main {class media_devices;}

namespace mediacapture::detail::devices_internals
{
    auto on_page_load(
            main::media_devices* media_devices)
            -> void;
};


#endif //SBROWSER2_DEVICES_INTERNALS_HPP
