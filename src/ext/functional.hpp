#ifndef SBROWSER2_FUNCTIONAL_HPP
#define SBROWSER2_FUNCTIONAL_HPP

#include "ext/tuple.hpp"
#include "ext/type_traits.hpp"
#include <function2/function2.hpp>


// TODO : test performance against C++ std implementations (bind_front)
// TODO : are arguments being forwarded out of tuple into method?
// TODO : are arguments being forwarded correctly?


_EXT_BEGIN

template <typename ..._Valty>
using function = fu2::function<_Valty...>;

// bind arguments to the back of a method, so that when the partial-method is called with arguments, they will the front
// n arguments (using because std::bind_back isn't available yet on MSVC)
template <typename _Fx, typename ..._Types>
struct bind_back
{
public:
    explicit bind_back(const _Fx& _Func, _Types&&... _FixedArgs)
            : _Function{_Func}
            , _BackArgs{tuplet::make_tuple(std::forward<_Types>(_FixedArgs)...)}
    {
        // initialize the function and the back arguments, by forwarding the arguments into a tuple and setting this as
        // '_BackArgs' TODO: tuplet::forward_as_tuple doesn't work here
    }

    template <typename ..._Ty>
    constexpr auto operator()(_Ty&&... _VariableArgs) const
    {
        // forward the new arguments into a tuple, concatenate this to the beginning of the '_FrontArgs', and apply this
        // tuple to the '_Function', so that the function is invoked with all the arguments
        auto _FrontArgs = tuplet::make_tuple(std::forward<_Ty>(_VariableArgs)...);
        return tuplet::apply(_Function, tuplet::tuple_cat(_FrontArgs, _BackArgs));
    }

private:
    const _Fx& _Function;
    _EXT tuple<_Types...> _BackArgs;
};


// bind arguments to the front of a method, so that when the partial-method is called with arguments, they will the back
// n arguments (using because std::bind_back isn't available yet on MSVC, so conform with ext::bind_back)
template <typename _Fx, typename ..._Types>
struct bind_front
{
public:
    explicit bind_front(const _Fx& _Func, _Types&&... _FixedArgs)
            : _Function{_Func}
            , _FrontArgs{tuplet::make_tuple(std::forward<_Types>(_FixedArgs)...)}
    {
        // initialize the function and the front arguments, by forwarding the arguments into a tuple and setting this as
        // as '_FrontArgs' TODO: tuplet::forward_as_tuple doesn't work here
    };

    constexpr auto operator()(auto&&... _VariableArgs) const
    {
        // forward the new arguments into a tuple, concatenate this to the end of the '_BackArgs', and apply this tuple
        // to the '_Function', so that the function is invoked with all the arguments
        auto _BackArgs = tuplet::make_tuple(std::forward<decltype(_VariableArgs)>(_VariableArgs)...);
        return tuplet::apply(_Function, tuplet::tuple_cat(_FrontArgs, _BackArgs));
    }

private:
    const _Fx& _Function;
    _EXT tuple<_Types...> _FrontArgs;
};

_EXT_END


#endif //SBROWSER2_FUNCTIONAL_HPP
