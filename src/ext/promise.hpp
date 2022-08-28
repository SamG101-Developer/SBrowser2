#ifndef SBROWSER2_SRC_EXT_PROMISE_HPP
#define SBROWSER2_SRC_EXT_PROMISE_HPP

#include <future>
#include "keywords.hpp"


_EXT_BEGIN


template <typename ...Ts>
class promise
{
    template <typename U>
    auto resolve(U&& value) -> promise<Ts...>&;

    template <typename U>
    auto reject(U&& exception) -> promise<Ts...>&;

    template <typename U, typename V>
    auto react(U&& steps0, V&& steps1 = []{}) -> promise<Ts...>&;
};


_EXT_END


#endif //SBROWSER2_SRC_EXT_PROMISE_HPP
