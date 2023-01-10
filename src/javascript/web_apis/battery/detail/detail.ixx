module;
#include "ext/macros.hpp"


export module apis.bettery.detail;
import ext.core;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(battery)
{
    template <ext::type_is<ext::boolean, ext::number<double>> T>
    auto update_battery_status_and_notify(
            T* property,
            T&& new_value,
            ext::string&& event_name)
            -> void;
}
