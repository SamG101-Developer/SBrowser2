module;
#include "ext/macros.hpp"


export module apis.gyroscope.gyroscope;
import apis.sensors.sensor;


DEFINE_PUBLIC_CLASS(gyroscope, gyroscope) final
        : public sensors::sensor
{
public typedefs:
    using gyroscope_sensor_options_t = ext::map<ext::string, ext::any>;

public constructors:
    DOM_CTORS(gyroscope);
    gyroscope(gyroscope_sensor_options_t&& sensor_options);
    MAKE_PIMPL(gyroscope);
    MAKE_V8_AVAILABLE(WINDOW | SECURE);

private js_properties:
    DEFINE_GETTER(x, ext::number<double>);
    DEFINE_GETTER(y, ext::number<double>);
    DEFINE_GETTER(z, ext::number<double>);
};
