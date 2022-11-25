#ifndef SBROWSER2_SRC_EXT_INITIALIZER_LIST_HPP
#define SBROWSER2_SRC_EXT_INITIALIZER_LIST_HPP

#include <initializer_list>
#include "ext/variadic.hpp"


_EXT_BEGIN
    template <typename T>
    auto make_initializer_list_repeat(T&& argument, size_t repeat) -> std::initializer_list<T>;

    template <typename ...Args>
    auto make_initializer_list(Args&&... arguments) -> std::initializer_list<_EXT nth_variadic_type_t<0, Args...>>
    {return {std::forward<Args>(arguments)...};}

    using std::initializer_list;
_EXT_END


#endif //SBROWSER2_SRC_EXT_INITIALIZER_LIST_HPP
