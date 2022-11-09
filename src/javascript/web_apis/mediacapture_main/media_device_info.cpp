#include "media_device_info.hpp"
#include "media_device_info_private.hpp"
#include "v8-json.h"


auto mediacapture::main::media_device_info::get_device_id() const -> ext::string_view
{
    ACCESS_PIMPL(const media_device_info);
    return d->device_id;
}


auto mediacapture::main::media_device_info::get_group_id() const -> ext::string_view
{
    ACCESS_PIMPL(const media_device_info);
    return d->group_id;
}


auto mediacapture::main::media_device_info::get_label() const -> ext::string_view
{
    ACCESS_PIMPL(const media_device_info);
    return d->label;
}


auto mediacapture::main::media_device_info::get_kind() const -> detail::media_device_kind_t
{
    ACCESS_PIMPL(const media_device_info);
    return d->kind;
}


mediacapture::main::media_device_info::operator ext::string() const
{
    auto e = js::env::env::relevant(this);
    auto json_string_v8 = v8::JSON::Stringify(e.js.realm(), v8pp::to_v8(e.js.agent(), this)).ToLocalChecked();
    auto json_string_cpp = v8pp::from_v8<ext::string>(e.js.agent(), json_string_v8);
    return json_string_cpp;
}
