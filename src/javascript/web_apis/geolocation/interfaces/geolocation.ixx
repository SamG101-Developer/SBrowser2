module;
#include "ext/macros.hpp"


export module apis.geolocation.geolocation;
import apis.dom_object;


DEFINE_PUBLIC_CLASS(geolocation, geolocation) final
        : virtual public dom_object
{
public constructors:
    geolocation();
    MAKE_PIMPL(geolocation);
    MAKE_V8_AVAILABLE(WINDOW);

private js_methods:
    auto get_current_position(detail::position_callback_t&& success_callback, detail::position_error_callback_t&& error_callback, detail::position_options_t&& options) -> void;
    auto watch_position(detail::position_callback_t&& success_callback, detail::position_error_callback_t&& error_callback, detail::position_options_t&& options) -> ext::number<long>;
    auto clear_watch(ext::number<long> watch_id) -> void;
};
