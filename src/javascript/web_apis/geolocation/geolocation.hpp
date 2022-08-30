#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_GEOLOCATION_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_GEOLOCATION_HPP

#include "dom_object.hpp"
namespace geolocation {class geolocation;}

#include USE_INNER_TYPES(geolocation);


class geolocation::geolocation
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(geolocation);
    geolocation() = default;

public js_methods:
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
            const ext::number<long>& watch_id)
            -> void;

private js_slots:
    ext::slot<geolocation_position*> s_cached_position;
    ext::slot<ext::vector<ext::number<unsigned long>>> s_watch_ids;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_GEOLOCATION_HPP