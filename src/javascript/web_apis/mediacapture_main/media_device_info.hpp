#pragma once
#ifndef SBROWSER2_MEDIA_DEVICE_INFO_HPP
#define SBROWSER2_MEDIA_DEVICE_INFO_HPP

#include "dom_object.hpp"
namespace mediacapture::main {class media_device_info;}

#include "_typedefs.hpp"


class mediacapture::main::media_device_info
        : public virtual dom_object
{
public js_properties:
    ext::property<ext::string> device_id;
    ext::property<ext::string> label;
    ext::property<ext::string> group_id;
    ext::property<detail::media_device_kind_t> kind;

public cpp_methods:
    auto to_json() const -> ext::string override;
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
};


#endif //SBROWSER2_MEDIA_DEVICE_INFO_HPP
