#ifndef SBROWSER2_FUNCTIONAL_HPP
#define SBROWSER2_FUNCTIONAL_HPP

#include "ext/tuple.hpp"
#include "ext/type_traits.hpp"
#include <function2/function2.hpp>
namespace ext {template <typename ..._Ts> using function = fu2::function<_Ts...>;}
namespace ext {template <typename _Fx, typename ..._Types> struct bind_back;}
namespace ext {template <typename _Fx, typename ..._Types> struct bind_front;}


// TODO : test performance against C++ std implementations (bind_front)
// TODO : are arguments being forwarded out of tuple into method?
template <typename _Fx, typename ..._Types>
struct ext::bind_back
{
public:
    explicit bind_back(const _Fx& _Func, _Types&&... _FixedArgs)
            : _Function{_Func}
            , _BackArgs{tuplet::make_tuple(std::forward<_Types>(_FixedArgs)...)}
    {}

    constexpr auto operator()(auto&&... _VariableArgs) const
    {
        auto _FrontArgs = tuplet::make_tuple(std::forward<decltype(_VariableArgs)>(_VariableArgs)...);
        return tuplet::apply(_Function, tuplet::tuple_cat(_FrontArgs, _BackArgs));
    }

private:
    const _Fx& _Function;
    ext::tuple<_Types...> _BackArgs;
};


template <typename _Fx, typename ..._Types>
struct ext::bind_front
{
public:
    explicit bind_front(const _Fx& _Func, _Types&&... _FixedArgs)
            : _Function{_Func}
            , _FrontArgs{tuplet::make_tuple(std::forward<_Types>(_FixedArgs)...)}
    {};

    constexpr auto operator()(auto&&... _VariableArgs) const
    {
        auto _BackArgs = tuplet::make_tuple(std::forward<decltype(_VariableArgs)>(_VariableArgs)...);
        return tuplet::apply(_Function, tuplet::tuple_cat(_FrontArgs, _BackArgs));
    }

private:
    const _Fx& _Function;
    ext::tuple<_Types...> _FrontArgs;
};


#endif //SBROWSER2_FUNCTIONAL_HPP
