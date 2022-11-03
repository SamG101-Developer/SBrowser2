#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BATTERY_BATTERY_MANAGER_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BATTERY_BATTERY_MANAGER_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom/nodes/event_target_private.hpp"

#include "ext/boolean.hpp"
#include "ext/number.hpp"

#include <hwinfo/battery.h>


DEFINE_PRIVATE_CLASS(battery, battery_manager) : dom::nodes::event_target_private
{
    auto charging() const -> ext::boolean {return battery->charging();};
    auto charging_time() const -> ext::number<double> {/* TODO */};
    auto discharging_time() const -> ext::number<double> {/* TODO */};
    auto level() const -> ext::number<double> {/* TODO */};

    std::unique_ptr<hwinfo::Battery> battery;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BATTERY_BATTERY_MANAGER_PRIVATE_HPP
