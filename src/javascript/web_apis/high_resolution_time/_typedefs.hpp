#ifndef SBROWSER2_HIGH_RESOLUTION_TIME_TYPEDEFS_HPP
#define SBROWSER2_HIGH_RESOLUTION_TIME_TYPEDEFS_HPP


#include "ext/number.hpp"

namespace high_resolution_time
{
    using dom_high_res_time_stamp = ext::number<double>;
    using epoch_time_stamp        = ext::number<ulonglong>;
}

#endif //SBROWSER2_HIGH_RESOLUTION_TIME_TYPEDEFS_HPP
