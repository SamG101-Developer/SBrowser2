#include "media_device_info.hpp"
#include "media_device_info_private.hpp"


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
