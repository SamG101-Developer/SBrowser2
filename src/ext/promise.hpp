#ifndef SBROWSER2_SRC_EXT_PROMISE_HPP
#define SBROWSER2_SRC_EXT_PROMISE_HPP

#include <future>
#include "keywords.hpp"


_EXT_BEGIN


template <typename T>
class promise
{
    template <typename T>
    auto resolve(T&& value) -> void;

    template <typename T>
    auto reject(T&& exception) -> void;

    template <typename T, typename U>
    auto react(T&& steps0, U&& steps1 = []{}) -> void;
};


_EXT_END


#endif //SBROWSER2_SRC_EXT_PROMISE_HPP
