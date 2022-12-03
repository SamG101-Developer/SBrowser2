#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_USER_TIMING_PERFORMANCE_MEASURE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_USER_TIMING_PERFORMANCE_MEASURE_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "performance_timeline/performance_entry_private.hpp"




DEFINE_PRIVATE_CLASS(user_timing, performance_measure) : performance_timeline::performance_entry_private
{
    ext::any detail;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_USER_TIMING_PERFORMANCE_MEASURE_PRIVATE_HPP
