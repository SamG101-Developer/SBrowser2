#ifndef SBROWSER2_FUNCTIONAL_HPP
#define SBROWSER2_FUNCTIONAL_HPP

#include <functional>
#include <type_traits>
namespace ext {template <typename _Fx, typename ..._Types> struct bind_back;}
namespace ext {template <typename _Fx, typename ..._Types> struct bind_front;}


// TODO : test performance against C++ std implementations (bind_front)
// TODO : are arguments being forwarded out of tuple into method?
template <typename _Fx, typename ..._Types>
struct ext::bind_back
{
public:
    explicit bind_back(_Fx&& _Func, _Types&&... _FixedArgs)
            : _Function{std::forward<_Fx>(_Func)}
            , _BackArgs{std::forward_as_tuple(std::forward<_Types>(_FixedArgs)...)}
    {}

    template <typename ..._Types2>
    auto operator()(_Types2&&... _VariableArgs)
    {
        auto _FrontArgs = std::make_tuple(std::forward<_Types2>(_VariableArgs)...);
        auto _TotalArgs = std::tuple_cat(_FrontArgs, _BackArgs);
        return std::apply(std::forward<_Fx>(_Function), _TotalArgs);
    }

private:
    _Fx&& _Function;
    std::tuple<_Types...> _BackArgs;
};


template <typename _Fx, typename ..._Types>
struct ext::bind_front
{
public:
    explicit bind_front(_Fx&& _Func, _Types&&... _FixedArgs)
            : _Function{std::forward<_Fx>(_Func)}
            , _FrontArgs{std::forward_as_tuple(std::forward<_Types>(_FixedArgs)...)}
    {};

    template <typename ..._Types2>
    auto operator()(_Types2&&... _VariableArgs)
    {
        auto _BackArgs  = std::make_tuple(std::forward<_Types2>(_VariableArgs)...);
        auto _TotalArgs = std::tuple_cat(_FrontArgs, _BackArgs);
        return std::apply(std::forward<_Fx>(_Function), _TotalArgs);
    }

private:
    _Fx&& _Function;
    std::tuple<_Types...> _FrontArgs;
};


#endif //SBROWSER2_FUNCTIONAL_HPP
