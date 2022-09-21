#pragma once
#ifndef SBROWSER2_TIME_INTERNALS_HPP
#define SBROWSER2_TIME_INTERNALS_HPP

#include "ext/optional.hpp"
#include <v8-local-handle.h>
#include <v8-object.h>
#include INCLUDE_INNER_TYPES(hr_time)
namespace hr_time::hr_time {class performance;}

namespace hr_time::detail
{
    auto get_time_origin_timestamp(
            v8::Local<v8::Object> global_object)
            -> dom_high_res_time_stamp;

    auto coarsen_time(
            const dom_high_res_time_stamp& time_stamp,
            ext::boolean cross_origin_isolated_capability = false)
            -> dom_high_res_time_stamp;

    auto relative_hr_time(
            const dom_high_res_time_stamp& time_stamp,
            v8::Local<v8::Object> global_object)
            -> dom_high_res_time_stamp;

    auto relative_high_resolution_coarse_time(
            const dom_high_res_time_stamp& coarse_time,
            v8::Local<v8::Object> global_object)
            -> dom_high_res_time_stamp;

    auto current_hr_time(
            v8::Local<v8::Object> global_object)
            -> dom_high_res_time_stamp;

    auto coarsen_shared_current_time(
            ext::boolean cross_origin_isolated_capability = false)
            -> dom_high_res_time_stamp;

    auto unsafe_shared_current_time()
            -> dom_high_res_time_stamp;

    auto epoch_relative_time_stamp(
            const ext::optional<epoch_time_stamp>& time_stamp)
            -> epoch_time_stamp;
}


#endif //SBROWSER2_TIME_INTERNALS_HPP
