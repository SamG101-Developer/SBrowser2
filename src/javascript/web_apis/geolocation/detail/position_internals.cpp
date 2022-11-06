#include "position_internals.hpp"

#include "javascript/environment/realms_2.hpp"

#include "dom/nodes/document.hpp"
#include "geolocation/geolocation.hpp"
#include "html/detail/document_internals.hpp"
#include "permissions/detail/permission_internals.hpp"

#include INCLUDE_INNER_TYPES(geolocation)
#include INCLUDE_INNER_TYPES(page_visibility)
#include INCLUDE_INNER_TYPES(permissions)

#include <range/v3/action/remove.hpp>


auto geolocation::detail::request_position(
        geolocation* geolocation,
        detail::position_callback_t&& success_callback,
        detail::position_error_callback_t&& error_callback,
        detail::position_options_t&& options,
        ext::optional<ext::number<long>> watch_id)
        -> void
{
    JS_REALM_GET_CURRENT
    decltype(auto) document = js::env::realms::get<dom::nodes::document*>(current_global_object, "$AssociatedDocument");

    if (!html::detail::allowed_to_use(document, "geolocation"))
    {
        if (watch_id.has_value()) geolocation->s_watch_ids |= ranges::actions::remove(watch_id);
        callback_with_error(std::move(error_callback), error_reason_t::PERMISSION_DENIED);
        return;
    }

    while (document->visibility_state() != page_visibility::detail::visibility_state_t::VISIBLE)
        continue;

    permissions::detail::permissions_descriptor_t descriptor{{"name", "geolocation"}};
    auto permission = permissions::detail::request_permission_to_use(std::move(descriptor));

    if (permission == permissions::detail::permission_state_t::DENIED)
    {
        if (watch_id.has_value()) geolocation->s_watch_ids |= ranges::actions::remove(watch_id);
        callback_with_error(std::move(error_callback), error_reason_t::PERMISSION_DENIED);
        return;
    }

    acquire_position(std::move(success_callback), std::move(error_callback), std::move(options), watch_id);
    return_if (!watch_id.has_value());

    // TODO
}
