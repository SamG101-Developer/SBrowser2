#include "position_internals.hpp"

#include "javascript/environment/realms.hpp"

#include "dom/nodes/document.hpp"
#include "dom/nodes/document_private.hpp"
#include "dom/nodes/window.hpp"
#include "dom/nodes/window_private.hpp"

#include "geolocation/_typedefs.hpp"
#include "geolocation/geolocation.hpp"
#include "geolocation/geolocation_private.hpp"

#include "permissions/_typedefs.hpp"
#include "permissions/detail/permission_internals.hpp"

#include "html/detail/document_internals.hpp"
#include "page_visibility/_typedefs.hpp"

#include <range/v3/action/remove.hpp>


auto geolocation::detail::request_position(
        geolocation* geolocation,
        detail::position_callback_t&& success_callback,
        detail::position_error_callback_t&& error_callback,
        detail::position_options_t&& options,
        ext::optional<ext::number<long>> watch_id)
        -> void
{
    auto e = js::env::env::current();
    decltype(auto) document = e.cpp.global<dom::nodes::window>()->d_func()->document.get();

    if (!html::detail::allowed_to_use(document, u"geolocation"))
    {
        if (watch_id.has_value()) geolocation->d_func()->watch_ids |= ranges::actions::remove(watch_id);
        callback_with_error(std::move(error_callback), error_reason_t::PERMISSION_DENIED);
        return;
    }

    while (document->visibility_state() != page_visibility::detail::visibility_state_t::VISIBLE)
        continue;

    permissions::detail::permissions_descriptor_t descriptor{{u"name", u"geolocation"}};
    auto permission = permissions::detail::request_permission_to_use(std::move(descriptor));

    if (permission == permissions::detail::permission_state_t::DENIED)
    {
        if (watch_id.has_value()) geolocation->d_func()->watch_ids |= ranges::actions::remove(watch_id);
        callback_with_error(std::move(error_callback), error_reason_t::PERMISSION_DENIED);
        return;
    }

    acquire_position(std::move(success_callback), std::move(error_callback), std::move(options), watch_id);
    return_if (!watch_id.has_value());

    // TODO
}
