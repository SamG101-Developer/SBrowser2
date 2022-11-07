#ifndef SBROWSER2_SRC_EXT_VARIADIC_HPP
#define SBROWSER2_SRC_EXT_VARIADIC_HPP

#include "ext/tuple.hpp"
#include "ext/variant.hpp"


_EXT_BEGIN
    template <size_t N, typename ...Args>
    auto nth_variadic_value(Args&&... args)
    {return ext::get<N>(ext::make_tuple<Args...>(std::forward<Args>(args)...));}

    template <size_t Index, typename ...Types>
    struct nth_variadic_type
    {using type = decltype(_EXT get<Index>(_EXT variant<Types...>{}));};

    template <size_t Index, typename ...Types>
    using nth_variadic_type_t = typename nth_variadic_type<Index, Types...>::type;
_EXT_END


#endif //SBROWSER2_SRC_EXT_VARIADIC_HPP
