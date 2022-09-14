#include "time_internals.hpp"

#include "javascript/environment/realms_2.hpp"
#include <chrono>


auto hr_time::detail::get_time_origin_timestamp(
        v8::Local<v8::Object> global_object)
        -> dom_high_res_time_stamp
{
    // get the 'time_origin' of the 'global_object's time origin; when it eas created. get the 'global_objects'
    // cross-origin isolated capability as a boolean, and coarsen the 'time_origin' wth this boolean. return the
    // coarsened time
    auto time_origin = javascript::environment::realms_2::get<dom_high_res_time_stamp>(global_object, "time_origin");
    auto cross_origin_isolated_capability = javascript::environment::realms_2::get<ext::boolean>(global_object, "cross_origin_isolated_capability");
    auto coarse_time = coarsen_time(time_origin, std::move(cross_origin_isolated_capability));
    return coarse_time;
}


auto hr_time::detail::coarsen_time(
        const dom_high_res_time_stamp& time_stamp,
        ext::boolean cross_origin_isolated_capability)
        -> dom_high_res_time_stamp
{
    // set the 'time_resolution' to 5ms if the 'time_stamp' has 'cross_origin_isolated_capability'; otherwise 100ms.
    // jitter the time by adding a random value limited by the time_resolution to the 'time_stamp'. next, the time is
    // coarsened by rounding the 'jitter_time' to the nearest 'time_resolution'. return the 'coarse_time'
    auto time_resolution = cross_origin_isolated_capability ? 5 : 100;
    auto jitter_time = time_stamp + std::rand() % time_resolution;
    auto coarse_time = ext::round(jitter_time, time_resolution);
    return coarse_time;
}


auto hr_time::detail::relative_hr_time(
        const dom_high_res_time_stamp& time_stamp,
        v8::Local<v8::Object> global_object)
        -> dom_high_res_time_stamp
{
    auto cross_origin_isolated_capability = javascript::environment::realms_2::get<ext::boolean>(global_object, "cross_origin_isolated_capability");
    auto coarse_time = coarsen_time(time_stamp, std::move(cross_origin_isolated_capability));
    auto relative_time = relative_high_resolution_coarse_time(coarse_time, global_object);
    return relative_time;
}


auto hr_time::detail::relative_high_resolution_coarse_time(
        const dom_high_res_time_stamp& coarse_time,
        v8::Local<v8::Object> global_object)
        -> dom_high_res_time_stamp
{
    auto time_origin = get_time_origin_timestamp(global_object);
    auto time_difference = coarse_time - time_origin;
    return time_difference;
}


auto hr_time::detail::current_hr_time(
        v8::Local<v8::Object> global_object)
        -> dom_high_res_time_stamp
{
    auto current_time = unsafe_shared_current_time();
    auto relative_time = relative_hr_time(current_time, global_object);
    return relative_time;
}


auto hr_time::detail::coarsen_shared_current_time(
        ext::boolean cross_origin_isolated_capability)
        -> dom_high_res_time_stamp
{
    auto current_time = unsafe_shared_current_time();
    auto coarse_time = coarsen_time(current_time, std::move(cross_origin_isolated_capability));
    return coarse_time;
}


auto hr_time::detail::unsafe_shared_current_time()
        -> dom_high_res_time_stamp
{
    auto current_time = std::chrono::steady_clock::now().time_since_epoch().count();
    return current_time;
}


auto hr_time::detail::epoch_relative_time_stamp(
        const ext::optional<epoch_time_stamp>& time_stamp)
        -> epoch_time_stamp
{
    auto time_stamp_corrected = time_stamp.value_or(unsafe_shared_current_time());
    auto time_stamp_as_duration = std::chrono::duration<epoch_time_stamp::value_t>{time_stamp_corrected};
    auto time_stamp_as_time_point = std::chrono::time_point<std::chrono::steady_clock>{time_stamp_as_duration};
    auto time_since_epoch = time_stamp_as_time_point.time_since_epoch().count();
    return time_since_epoch;
}
