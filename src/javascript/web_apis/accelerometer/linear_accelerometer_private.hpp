#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ACCELEROMETER_LINEAR_ACCELEROMETER_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ACCELEROMETER_LINEAR_ACCELEROMETER_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "accelerometer/accelerometer_private.hpp"


DEFINE_PRIVATE_CLASS(accelerometer, linear_accelerometer)
        : accelerometer_private
{
    MAKE_QIMPL(linear_accelerometer);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ACCELEROMETER_LINEAR_ACCELEROMETER_PRIVATE_HPP
