#include "geolocation.hpp"

#include "javascript/environment/realms_2.hpp"

#include "dom/detail/node_internals.hpp"
#include "dom/nodes/document.hpp"

#include <range/v3/action/remove.hpp>


auto geolocation::geolocation::get_current_position(
        detail::position_callback_t&& success_callback,
        detail::position_error_callback_t&& error_callback,
        detail::position_options_t&& options)
        -> void
{
    JS_REALM_GET_CURRENT
    decltype(auto) document = javascript::environment::realms_2::get<dom::nodes::document*>(current_global_object, "$AssociatedDocument");
    if (!dom::detail::is_document_fully_active(document))
    {
        detail::callback_with_error(this, std::move(error_callback), detail::error_reason_t::POSITION_UNAVAILABLE);
        return;
    }

    go [
            success_callback = std::move(success_callback),
            error_callback = std::move(error_callback),
            options = std::move(options)]
            mutable
    {detail::request_position(this, std::move(success_callback), std::move(error_callback), std::move(options));};
}


auto geolocation::geolocation::watch_position(
        detail::position_callback_t&& success_callback,
        detail::position_error_callback_t&& error_callback,
        detail::position_options_t&& options)
        -> ext::number<long>
{
    JS_REALM_GET_CURRENT
    decltype(auto) document = javascript::environment::realms_2::get<dom::nodes::document*>(current_global_object, "$AssociatedDocument");
    if (!dom::detail::is_document_fully_active(document))
    {
        detail::callback_with_error(this, std::move(error_callback), detail::error_reason_t::POSITION_UNAVAILABLE);
        return 0;
    }

    auto watch_id = ext::number<ulong>::random();
    s_watch_ids().emplace_back(std::move(watch_id));

    go [
            success_callback = std::move(success_callback),
            error_callback = std::move(error_callback),
            options = std::move(options),
            watch_id = std::move(watch_id)]
            mutable
    {detail::request_position(this, std::move(success_callback), std::move(error_callback), std::move(options), std::move(watch_id));};

    return watch_id;
}


auto geolocation::geolocation::clear_watch(
        const ext::number<long>& watch_id)
        -> void
{
    s_watch_ids() |= ranges::actions::remove(watch_id);
}
