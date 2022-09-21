#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BATTERY_DETAIL_ALGORITHM_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BATTERY_DETAIL_ALGORITHM_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/number.hpp"
#include "ext/property.hpp"
#include "ext/string.hpp"
#include USE_INNER_TYPES(battery)


namespace battery::algorithm_internals
{
    template <type_is<ext::boolean, ext::number<double>> T>
    auto update_battery_status_and_notify(
            ext::property<T>& property,
            T&& new_value,
            ext::string&& event_name)
            -> void;
}


struct battery::detail::battery_manager_t
{
    ext::boolean charging = true;
    ext::number<double> charging_time = 0.0;
    ext::number<double> discharging_time = ext::number<double>::inf();
    ext::number<double> level = 1.0;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BATTERY_DETAIL_ALGORITHM_INTERNALS_HPP
