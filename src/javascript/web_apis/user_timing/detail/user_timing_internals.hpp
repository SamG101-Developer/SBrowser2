#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_USER_TIMING_DETAIL_USER_TIMING_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_USER_TIMING_DETAIL_USER_TIMING_INTERNALS_HPP

#include "ext/keywords.ixx"
#include INCLUDE_INNER_TYPES(hr_time)


namespace user_timing::detail
{
    auto convert_mark_to_timestamp(
            ext::string_view mark)
            -> hr_time::dom_high_res_time_stamp;

    auto convert_name_to_timestamp(
            ext::string_view name)
            -> hr_time::dom_high_res_time_stamp;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_USER_TIMING_DETAIL_USER_TIMING_INTERNALS_HPP
