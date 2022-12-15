module;
#include "ext/macros/pimpl.hpp"
#include <hwinfo/battery.h>


export module apis.battery.battery_manager_private;
import ext.boolean;
import ext.number;


DEFINE_PRIVATE_CLASS(battery, battery_manager)
        : dom::event_target_private
{
    MAKE_QIMPL(battery_manager);

    auto charging() const -> ext::boolean;
    auto charging_time() const -> ext::number<double>;
    auto discharging_time() const -> ext::number<double>;
    auto level() const -> ext::number<double>;

    std::unique_ptr<hwinfo::Battery> battery;
};
