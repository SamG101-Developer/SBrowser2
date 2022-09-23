#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BATTERY_BATTERY_MANAGER_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BATTERY_BATTERY_MANAGER_PRIVATE_HPP

#include "dom/nodes/event_target_private.hpp"

#include "ext/boolean.hpp"
#include "ext/pimpl.hpp"
#include "ext/number.hpp"


DEFINE_PRIVATE_CLASS(battery, battery_manager) : dom::nodes::event_target_private
{
    ext::boolean charging = true;
    ext::number<double> charging_time = 0.0;
    ext::number<double> discharging_time = ext::number<double>::inf();
    ext::number<double> level = 1.0;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BATTERY_BATTERY_MANAGER_PRIVATE_HPP
