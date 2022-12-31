module;
#include "ext/macros.hpp"


export module apis.ambient_light.ambient_light_sensor;
import apis.sensors.sensor;

IMPORT_ALL_TYPES(sensors);


DEFINE_PUBLIC_CLASS(ambient_light, ambient_light_sensor) final
        : public sensors::sensor
{
public constructors:
    ambient_light_sensor(ext::map<ext::string, ext::any>&& options = {});
    DOM_CTORS(ambient_light_sensor);
    MAKE_PIMPL(ambient_light_sensor);
    MAKE_V8_AVAILABLE(WINDOW | SECURE);

private js_properties:
    DEFINE_GETTER(illuminance, ext::number<double>);
};
