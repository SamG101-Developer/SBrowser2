module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/namespaces.hpp"

export module ext.time;
import ext.number;


_EXT_BEGIN

export class time final
{
public:
    template <typename F>
    static auto time_method(F&& predicate, _EXT number<size_t> limit = 1uz) -> _EXT number<long long>;
};


export template <typename F>
auto time::time_method(
        F&& predicate,
        _EXT number<size_t> limit)
        -> _EXT number<long long>
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
