#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BATTERY_DETAIL_ALGORITHM_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BATTERY_DETAIL_ALGORITHM_INTERNALS_HPP



#include "ext/property.hpp"



namespace battery::algorithm_internals
{
    template <ext::type_is<ext::boolean, ext::number<double>> T>
    auto update_battery_status_and_notify(
            T* property,
            T&& new_value,
            ext::string&& event_name)
            -> void;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BATTERY_DETAIL_ALGORITHM_INTERNALS_HPP
