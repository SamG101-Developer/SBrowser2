#include "abstract_operations_internals.hpp"

#include USE_INNER_TYPES(dom)
#include "dom/detail/exception_internals.hpp"
#include "accelerometer/accelerometer.hpp"
#include "sensors/detail/sensor_internals.hpp"

#include <typeinfo>


template <inherit<accelerometer::accelerometer> T>
auto accelerometer::detail::construct_accelerometer_object(
        T* object,
        accelerometer_sensor_options_t&& options) -> void
{
    dom::detail::throw_v8_exception_formatted<SECURITY_ERR>(
            [object] {return !sensors::detail::check_sensor_policy_controlled_features(*object->m_sensor);},
            ext::string{typeid(T).name()} + " cannot be created due to a failed check in the sensor policy controlled features");
}
