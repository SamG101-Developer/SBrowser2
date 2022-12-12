#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PROXIMITY_PROXIMITY_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PROXIMITY_PROXIMITY_HPP


namespace proximity {class proximity;}
namespace proximity {class proximity_private;}

#include INCLUDE_INNER_TYPES(proximity)


class proximity::proximity
        : public sensors::sensor
{
public constructors:
    proximity(detail::proximity_sensor_options_t&& options = {});
    DOM_CTORS(proximity);
    MAKE_PIMPL(proximity);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(distance, ext::number<double>);
    DEFINE_GETTER(max, ext::number<double>);
    DEFINE_GETTER(near, ext::boolean);
};

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PROXIMITY_PROXIMITY_HPP
