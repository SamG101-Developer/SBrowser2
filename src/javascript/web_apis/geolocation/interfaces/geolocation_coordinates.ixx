module;
#include "ext/macros.hpp"


export module apis.geolocation.geolocation_coordinates;
import apis.dom_object;


DEFINE_PUBLIC_CLASS(geolocation, geolocation_coordinates) final
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(geolocation_coordinates);
    MAKE_PIMPL(geolocation_coordinates);
    MAKE_V8_AVAILABLE(WINDOW | SECURE);

private js_properties:
    DEFINE_GETTER(accuracy, ext::number<double>);
    DEFINE_GETTER(latitude, ext::number<double>);
    DEFINE_GETTER(longitude, ext::number<double>);
    DEFINE_GETTER(altitude, ext::number<double>);
    DEFINE_GETTER(altitude_accuracy, ext::number<double>);
    DEFINE_GETTER(heading, ext::number<double>);
    DEFINE_GETTER(speed, ext::number<double>);
};
