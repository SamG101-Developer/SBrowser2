module apis.battery.battery_manager_private;

import ext.boolean;
import ext.number;


auto battery::battery_manager_private::charging() const -> ext::boolean
{
    return battery->charging();
}


auto battery::battery_manager_private::charging_time() const -> ext::number<double>
{
    return battery->capacity(); // TODO
}


auto battery::battery_manager_private::discharging_time() const -> ext::number<double>
{
    return battery->energyFull() / battery->energyNow();
}


auto battery::battery_manager_private::level() const -> ext::number<double>
{
    return battery->energyNow() != 0;
}
