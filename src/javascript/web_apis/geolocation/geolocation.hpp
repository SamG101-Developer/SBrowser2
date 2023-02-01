#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_GEOLOCATION_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_GEOLOCATION_HPP


namespace geolocation {class geolocation;}
namespace geolocation {class geolocation_private;}

#include INCLUDE_INNER_TYPES(geolocation)


class geolocation::geolocation
        : public virtual dom_object
{
public constructors:
    geolocation();
    MAKE_PIMPL(geolocation);
    MAKE_V8_AVAILABLE;

private js_methods:
    auto get_current_position(
            detail::position_callback_t&& success_callback,
            detail::position_error_callback_t&& error_callback = detail::position_error_callback_t{},
            detail::position_options_t&& options = {})
            -> void;

    auto watch_position(
            detail::position_callback_t&& success_callback,
            detail::position_error_callback_t&& error_callback = detail::position_error_callback_t{},
            detail::position_options_t&& options = {})
            -> ext::number<long>;

    auto clear_watch(
            ext::number<long> watch_id)
            -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_GEOLOCATION_HPP
