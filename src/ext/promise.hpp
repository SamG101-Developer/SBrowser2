#ifndef SBROWSER2_SRC_EXT_PROMISE_HPP
#define SBROWSER2_SRC_EXT_PROMISE_HPP

#include <future>
#include "keywords.hpp"


_EXT_BEGIN


template <typename ...Ts>
class promise
{
    template <typename U>
    auto resolve(U&& value) -> void;

    template <typename U>
    auto reject(U&& exception) -> void;

    template <typename U, typename V>
    auto react(U&& steps0, V&& steps1 = []{}) -> void;
};


_EXT_END


#endif //SBROWSER2_SRC_EXT_PROMISE_HPP
