#include "geolocation.hpp"

#include "javascript/environment/realms_2.hpp"

#include "dom/detail/node_internals.hpp"
#include "dom/nodes/document.hpp"
#include "dom/nodes/window.hpp"

#include <range/v3/action/remove.hpp>


geolocation::geolocation::geolocation()
{
    INIT_PIMPL(geolocation);
}


auto geolocation::geolocation::get_current_position(
        detail::position_callback_t&& success_callback,
        detail::position_error_callback_t&& error_callback,
        detail::position_options_t&& options)
        -> void
{
    JS_REALM_GET_CURRENT;
    decltype(auto) document = v8pp::from_v8<dom::nodes::window*>(current_agent, current_global_object)->d_func()->document;
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
    {
        detail::request_position(this, std::move(success_callback), std::move(error_callback), std::move(options));
    };
}


auto geolocation::geolocation::watch_position(
        detail::position_callback_t&& success_callback,
        detail::position_error_callback_t&& error_callback,
        detail::position_options_t&& options)
        -> ext::number<long>
{
    JS_REALM_GET_CURRENT;
    decltype(auto) document = v8pp::from_v8<dom::nodes::window*>(current_agent, current_global_object)->d_func()->document;
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
    {
        detail::request_position(this, std::move(success_callback), std::move(error_callback), std::move(options), std::move(watch_id));
    };

    return watch_id;
}


auto geolocation::geolocation::clear_watch(
        ext::number<long> watch_id)
        -> void
{
    ACCESS_PIMPL(geolocation);
    d->watch_ids |= ranges::actions::remove(watch_id);
}


auto geolocation::geolocation::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<geolocation>{isolate}
        .function("getCurrentPosition", &geolocation::get_current_position)
        .function("watchPosition", &geolocation::watch_position)
        .function("clearWatch", &geolocation::clear_watch)
        .auto_wrap_objects();

    return std::move(conversion);
}
