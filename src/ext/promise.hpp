#ifndef SBROWSER2_SRC_EXT_PROMISE_HPP
#define SBROWSER2_SRC_EXT_PROMISE_HPP

#include <future>
#include "boolean.hpp"
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

    ext::boolean is_resolved = false;
    ext::boolean is_rejected = false;
};


_EXT_END


#endif //SBROWSER2_SRC_EXT_PROMISE_HPP
