#pragma once
#ifndef SBROWSER2_TIME_INTERNALS_HPP
#define SBROWSER2_TIME_INTERNALS_HPP

#include "ext/optional.hpp"
#include <v8-local-handle.h>
#include <v8-object.h>
#include USE_INNER_TYPES(high_resolution_time)
namespace high_resolution_time::hr_time {class performance;}

namespace high_resolution_time::detail
{
    auto get_time_origin_timestamp(
            v8::Local<v8::Object> global_object)
            -> dom_high_res_time_stamp_t;

    auto coarsen_time(
            const dom_high_res_time_stamp_t& time_stamp,
            ext::boolean&& cross_origin_isolated_capability = false)
            -> dom_high_res_time_stamp_t;

    auto relative_high_resolution_time(
            const dom_high_res_time_stamp_t& time_stamp,
            v8::Local<v8::Object> global_object)
            -> dom_high_res_time_stamp_t;

    auto relative_high_resolution_coarse_time(
            const dom_high_res_time_stamp_t& coarse_time,
            v8::Local<v8::Object> global_object)
            -> dom_high_res_time_stamp_t;

    auto current_high_resolution_time(
            v8::Local<v8::Object> global_object)
            -> dom_high_res_time_stamp_t;

    auto coarsen_shared_current_time(
            ext::boolean&& cross_origin_isolated_capability = false)
            -> dom_high_res_time_stamp_t;

    auto unsafe_shared_current_time()
            -> dom_high_res_time_stamp_t;

    auto epoch_relative_time_stamp(
            const ext::optional<epoch_time_stamp_t>& time_stamp)
            -> epoch_time_stamp_t;
}


#endif //SBROWSER2_TIME_INTERNALS_HPP
