#pragma once
#ifndef SBROWSER2_TIME_INTERNALS_HPP
#define SBROWSER2_TIME_INTERNALS_HPP

#include "ext/optional.hpp"
#include "high_resolution_time/_typedefs.hpp"
#include <v8-local-handle.h>
#include <v8-object.h>
namespace high_resolution_time::hr_time {class performance;}

namespace high_resolution_time::detail::time_internals
{
    auto get_time_origin_timestamp(
            v8::Local<v8::Object> global_object)
            -> dom_high_res_time_stamp;

    auto coarsen_time(
            dom_high_res_time_stamp time_stamp,
            ext::boolean_view cross_origin_isolated_capability = false)
            -> dom_high_res_time_stamp;

    auto relative_high_resolution_time(
            dom_high_res_time_stamp time_stamp,
            v8::Local<v8::Object> global_object)
            -> dom_high_res_time_stamp;

    auto relative_high_resolution_coarse_time(
            dom_high_res_time_stamp coarse_time,
            v8::Local<v8::Object> global_object)
            -> dom_high_res_time_stamp;

    auto current_high_resolution_time(
            v8::Local<v8::Object> global_object)
            -> dom_high_res_time_stamp;

    auto coarsen_shared_current_time(
            ext::boolean_view cross_origin_isolated_capability = false)
            -> dom_high_res_time_stamp;

    auto unsafe_shared_current_time()
            -> dom_high_res_time_stamp;

    auto epoch_relative_time_stamp(
            ext::optional<epoch_time_stamp> time_stamp)
            -> epoch_time_stamp;
}


#endif //SBROWSER2_TIME_INTERNALS_HPP
