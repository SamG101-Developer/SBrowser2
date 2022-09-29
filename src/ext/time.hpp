#pragma once
#ifndef SBROWSER2_TIME_HPP
#define SBROWSER2_TIME_HPP

#include "ext/keywords.hpp"
#include "ext/number.hpp"
#include <chrono>


_EXT_BEGIN

class time final
{
public cpp_static_methods:
    template <typename F>
    static auto time_method(F&& predicate, number<size_t> limit = 1) -> number<long long>;
};


template <typename F>
auto time::time_method(
        F&& predicate,
        number<size_t> limit)
        -> number<long long>
{
    // get the time before and after execution of a method - there is the option to loop the method
    auto start = std::chrono::high_resolution_clock::now();
    for (number<size_t> index = 0; index < limit; ++index) predicate();
    auto stop = std::chrono::high_resolution_clock::now();

    // calculate the duration taken, cast to microseconds, and return the raw value
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    return duration.count();
}

_EXT_END


#endif //SBROWSER2_TIME_HPP
