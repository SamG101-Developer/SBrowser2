#ifndef SBROWSER2_NAVIGATOR_HPP
#define SBROWSER2_NAVIGATOR_HPP

#include "dom_object.hpp"
#include "storage/mixins/navigator_storage.hpp"
namespace html::other {class navigator;}

#include "ext/map.hpp"
namespace dom::other {class dom_exception;}
namespace clipboard {class clipboard;}
namespace mediacapture::main {class media_devices;}
namespace mediacapture::main {class media_stream;}
namespace permissions {class permission;}


class html::other::navigator
        : public virtual dom_object
        , public storage::mixins::navigator_storage
{
private aliases:
    using navigator_user_media_success_callback = ext::function<void(mediacapture::main::media_stream*)>;
    using navigator_user_media_error_callback   = ext::function<void(dom::other::dom_exception*)>;

public js_methods:
    /* MEDIACAPTURE_MAIN */
    auto get_user_media(
            ext::map<ext::string, ext::any>&& constraints,
            navigator_user_media_success_callback&& success_callback,
            navigator_user_media_error_callback&& error_callback)
            const -> void;

public js_properties:
    /* MEDIACAPTURE_MAIN */
    ext::property<std::unique_ptr<mediacapture::main::media_devices>> media_devices;

    /* PERMISSIONS */
    ext::property<std::unique_ptr<permissions::permission>> permissions;

    /* POINTER_EVENTS */
    ext::property<ext::number<long>> max_touch_points;

    /* CLIPBOARD */
    ext::property<std::unique_ptr<clipboard::clipboard>> clipboard;
};

#endif //SBROWSER2_NAVIGATOR_HPP
