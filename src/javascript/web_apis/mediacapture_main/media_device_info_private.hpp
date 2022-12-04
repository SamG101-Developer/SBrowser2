#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_MAIN_MEDIA_DEVICE_INFO_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_MAIN_MEDIA_DEVICE_INFO_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom_object_private.hpp"


#include INCLUDE_INNER_TYPES(mediacapture_main)


DEFINE_PRIVATE_CLASS(mediacapture::main, media_device_info) : virtual dom_object_private
{
    ext::string device_id;
    ext::string group_id;
    ext::string label;
    detail::media_device_kind_t kind;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_MAIN_MEDIA_DEVICE_INFO_PRIVATE_HPP
