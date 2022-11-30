#ifndef SBROWSER2_SRC_EXT_INITIALIZER_LIST_HPP
#define SBROWSER2_SRC_EXT_INITIALIZER_LIST_HPP

#include <better_braces.hpp>
#include "ext/variadic.hpp"


_EXT_BEGIN
    template <typename ...Ts>
    using initializer_list = better_braces::init<Ts...>;

    template <typename T>
    auto make_initializer_list_repeat(T&& argument, size_t repeat) -> _EXT initializer_list<T>;

    template <typename ...Args>
    auto make_initializer_list(Args&&... arguments) -> _EXT initializer_list<Args...>
    {return {std::forward<Args>(arguments)...};}
_EXT_END


#endif //SBROWSER2_SRC_EXT_INITIALIZER_LIST_HPP
