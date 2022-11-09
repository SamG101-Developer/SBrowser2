#include "geolocation.hpp"
#include "geolocation_private.hpp"

#include "javascript/environment/realms.hpp"

#include "dom/detail/node_internals.hpp"
#include "dom/nodes/document.hpp"
#include "dom/nodes/document_private.hpp"
#include "dom/nodes/window.hpp"
#include "dom/nodes/window_private.hpp"

#include "geolocation/_typedefs.hpp"
#include "geolocation/detail/position_internals.hpp"

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
    auto e = js::env::env::current();
    decltype(auto) document = e.cpp.global<dom::nodes::window*>()->d_func()->document.get();
    if (!dom::detail::is_document_fully_active(document))
    {
        detail::callback_with_error(this, std::move(error_callback), detail::error_reason_t::POSITION_UNAVAILABLE);
        return;
    }

    GO [
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
    ACCESS_PIMPL(geolocation);
    auto e = js::env::env::current();

    decltype(auto) document = e.cpp.global<dom::nodes::window*>()->d_func()->document.get();
    if (!dom::detail::is_document_fully_active(document))
    {
        detail::callback_with_error(this, std::move(error_callback), detail::error_reason_t::POSITION_UNAVAILABLE);
        return 0;
    }

    auto watch_id = ext::number<ulong>::random();
    d->watch_ids.emplace_back(std::move(watch_id));

    GO [
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


auto geolocation::geolocation::clear_watch(ext::number<long> watch_id) -> void
{
    ACCESS_PIMPL(geolocation);
    d->watch_ids |= ranges::actions::remove(watch_id);
}


auto geolocation::geolocation::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<geolocation>{isolate}
        .function("getCurrentPosition", &geolocation::get_current_position)
        .function("watchPosition", &geolocation::watch_position)
        .function("clearWatch", &geolocation::clear_watch)
        .auto_wrap_objects();

    return std::move(conversion);
}
