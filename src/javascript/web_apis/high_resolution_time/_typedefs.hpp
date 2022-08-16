#ifndef SBROWSER2_HIGH_RESOLUTION_TIME_TYPEDEFS_HPP
#define SBROWSER2_HIGH_RESOLUTION_TIME_TYPEDEFS_HPP

#include "ext/number.hpp"
#include "ext/type_traits.hpp"

namespace high_resolution_time::detail
{
    using dom_high_res_time_stamp_t = ext::number<double>;
    using epoch_time_stamp_t        = ext::number<ulonglong>;
}

#endif //SBROWSER2_HIGH_RESOLUTION_TIME_TYPEDEFS_HPP
