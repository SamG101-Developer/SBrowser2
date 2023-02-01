module;
#include "ext/macros.hpp"


export module apis.geolocation.detail;
import apis.geolocation.types;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(geolocation)
{
    // [6] - Geolocation
    /* [6.5] */ auto request_position(class geolocation* geolocation, position_callback_t&& success_callback, position_error_callback_t&& error_callback, position_options_t&& options, ext::optional<ext::number<long>> watch_id = ext::nullopt) -> void;
    /* [6.6] */ auto acquire_position(class geolocation* geolocation, position_callback_t&& success_callback, position_error_callback_t&& error_callback, position_options_t&& options, ext::optional<ext::number<long>> watch_id = ext::nullopt) -> void;
    /* [6.7] */ auto callback_with_error(position_error_callback_t&& callback, ext::number<ushort> code) -> void;
};
