export module apis.accelerometer.detail;


import apis.accelerometer.types;
import ext.any;
import ext.map;
import ext.string;

namespace accelerometer {class accelerometer;}


namespace accelerometer::detail
{
    /* [7.1] */ auto construct_accelerometer_object(accelerometer* sensor, ext::map<ext::string, ext::any>&& options) -> void;
}
