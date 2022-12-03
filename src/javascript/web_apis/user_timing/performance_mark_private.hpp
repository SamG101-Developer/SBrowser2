#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_USER_TIMING_PERFORMANCE_MARK_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_USER_TIMING_PERFORMANCE_MARK_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "performance_timeline/performance_entry_private.hpp"

#include "ext/any.hpp"
#include INCLUDE_INNER_TYPES(hr_time)


DEFINE_PRIVATE_CLASS(user_timing, performance_mark) : performance_timeline::performance_entry_private
{
    ext::any detail;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_USER_TIMING_PERFORMANCE_MARK_PRIVATE_HPP
