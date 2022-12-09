#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_DETAIL_POSITION_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_DETAIL_POSITION_INTERNALS_HPP

#include "ext/optional.ixx"

#include INCLUDE_INNER_TYPES(geolocation)

namespace geolocation {class geolocation;}


namespace geolocation::detail
{
    auto request_position(
            geolocation* geolocation,
            detail::position_callback_t&& success_callback,
            detail::position_error_callback_t&& error_callback,
            detail::position_options_t&& options,
            ext::optional<ext::number<long>> watch_id = ext::nullopt)
            -> void;

    auto acquire_position(
            geolocation* geolocation,
            detail::position_callback_t&& success_callback,
            detail::position_error_callback_t&& error_callback,
            detail::position_options_t&& options,
            ext::optional<ext::number<long>> watch_id = ext::nullopt)
            -> void;

    auto callback_with_error(
            position_error_callback_t&& callback,
            ext::number<ushort> code)
            -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_DETAIL_POSITION_INTERNALS_HPP
