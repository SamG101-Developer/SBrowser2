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
    template <typename _Fx>
    static auto time_method(_Fx&& _Pred, _EXT number<size_t> _Limit = 1) -> _EXT number<long long>;
};

_EXT_END


template <typename _Fx>
auto _EXT time::time_method(
        _Fx&& _Pred,
        _EXT number<size_t> _Limit)
        -> _EXT number<long long>
{
    // get the time before and after execution of a method - there is the option to loop the method
    auto _Start = std::chrono::high_resolution_clock::now();
    for (_EXT number<size_t> _Idx = 0; _Idx < _Limit; ++_Idx) _Pred();
    auto _Stop = std::chrono::high_resolution_clock::now();

    // calculate the duration taken, cast to microseconds, and return the raw value
    auto _Duration = std::chrono::duration_cast<std::chrono::microseconds>(_Stop - _Start);
    return _Duration.count();
}


#endif //SBROWSER2_TIME_HPP
