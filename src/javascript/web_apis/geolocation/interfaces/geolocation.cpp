module;
#include "ext/macros/custom_operator.hpp"
#include "ext/macros.hpp"

#include <range/v3/algorithm/remove.hpp>


module apis.geolocation.geolocation;
import apis.geolocation.types;


geolocation::geolocation::geolocation()
{
    INIT_PIMPL;
}


geolocation::geolocation::get_current_position(
        detail::position_callback_t&& success_callback,
        detail::position_error_callback_t&& error_callback,
        detail::position_options_t&& options)
{
    auto e = js::env::env::current();
    if (!html::detail::is_fully_active(e.cpp.global<dom::window*>()->d_func()->document.get()))
    {
        detail::callback_with_error(std::move(error_callback), POSITION_UNAVAILABLE);
        return;
    }

    _GO ext::bind_front(&detail::request_position, std::move(success_callback), std::move(error_callback), std::move(options));
}


geolocation::geolocation::watch_position(
        detail::position_callback_t&& success_callback,
        detail::position_error_callback_t&& error_callback,
        detail::position_options_t&& options)
{
    auto e = js::env::env::current();
    if (!html::detail::is_fully_active(e.cpp.global<dom::window*>()->d_func()->document.get()))
    {
        detail::callback_with_error(std::move(error_callback), POSITION_UNAVAILABLE);
        return 0;
    }

    ACCESS_PIMPL;
    auto watch_id = ext::random::random_int(0);
    d->watch_ids.emplace_back(watch_id);

    _GO ext::bind_front(&detail::request_position, std::move(success_callback), std::move(error_callback), std::move(options), watch_id);
    return watch_id;
}


geolocation::geolocation::clear_watch(ext::number<long> watch_id)
{
    ACCESS_PIMPL;
    d->watch_ids |= ranges::actions::remove(watch_id);
}
