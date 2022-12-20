module;
#include "ext/macros/namespaces.hpp"
#include <better_braces.hpp>

export module ext.core:initializer_list;
import :variadic;


_EXT_BEGIN
    export template <typename ...Ts>
    using initializer_list = better_braces::init<Ts...>;

    export template <typename T>
    auto make_initializer_list_repeat(T&& argument, size_t repeat) -> _EXT initializer_list<T>;

    export template <typename ...Args>
    auto make_initializer_list(Args&&... arguments) -> _EXT initializer_list<Args...>
    {return {std::forward<Args>(arguments)...};}
_EXT_END
