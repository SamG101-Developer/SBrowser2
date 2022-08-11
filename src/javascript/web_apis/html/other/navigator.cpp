#include "navigator.hpp"

#include "mediacapture_main/media_devices.hpp"


auto html::other::navigator::get_user_media(
        ext::map<ext::string, ext::any>&& constraints,
        html::other::navigator::navigator_user_media_success_callback&& success_callback,
        html::other::navigator::navigator_user_media_error_callback&& error_callback)
        const -> void
{
    auto promise = media_devices()->get_user_media(std::move(constraints));
    // TODO : call success_callback when std::promise set-value called
    // TODO : call error callback when std::promise set-error called
}
