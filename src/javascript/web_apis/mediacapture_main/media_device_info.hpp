#pragma once
#ifndef SBROWSER2_MEDIA_DEVICE_INFO_HPP
#define SBROWSER2_MEDIA_DEVICE_INFO_HPP


namespace mediacapture::main {class media_device_info;}
namespace mediacapture::main {class media_device_info_private;}

#include INCLUDE_INNER_TYPES(mediacapture_main)


class mediacapture::main::media_device_info
        : public virtual dom_object
{
public constructors:
    MAKE_PIMPL(media_device_info);
    MAKE_V8_AVAILABLE;
    MAKE_STRINGIFIER;

private js_properties:
    DEFINE_GETTER(device_id, ext::string_view);
    DEFINE_GETTER(group_id, ext::string_view);
    DEFINE_GETTER(label, ext::string_view);
    DEFINE_GETTER(kind, detail::media_device_kind_t);
};


#endif //SBROWSER2_MEDIA_DEVICE_INFO_HPP
