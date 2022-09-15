#ifndef SBROWSER2_FUNCTIONAL_HPP
#define SBROWSER2_FUNCTIONAL_HPP

#include "ext/concepts.hpp"
#include "ext/tuple.hpp"
#include <function2/function2.hpp>


// TODO : test performance against C++ std implementations (bind_front)
// TODO : are arguments being forwarded out of tuple into method?
// TODO : are arguments being forwarded correctly?


_EXT_BEGIN

using namespace fu2;


struct identity
{
    template <typename T>
    constexpr auto operator()(T&& object) const -> decltype(auto)
    {return std::forward<T>(object);}
};


struct negate
{
    template <typename T>
    constexpr auto operator()(T&& object) const -> decltype(auto)
    {return !std::forward<T>(object);}
};


template <callable F>
struct negate_function
{
    explicit negate_function(F&& predicate)
    {m_predicate = std::forward<F>(predicate);}

    template <typename ...Args>
    constexpr auto operator()(Args&&... arguments) const -> decltype(auto)
    {return !m_predicate(std::forward<Args>(arguments)...);}

private:
    F&& m_predicate;
};


struct invoke
{
    constexpr auto operator()(callable auto&& object) const -> decltype(auto)
    {return object();}
};


struct deref
{
    constexpr auto operator()(auto* object) const -> decltype(auto)
    {return *object;}
};


struct pointer_not_null
{
    constexpr auto operator()(auto* object) const -> decltype(auto)
    {return object != nullptr;}
};


namespace cmp {
struct lt
{
    constexpr auto operator()(auto&& lhs, auto&& rhs, auto&& pred = _EXT identity{}) -> _EXT boolean
    {return pred(std::forward<decltype(lhs)>) < rhs;}
};


struct le
{
    constexpr auto operator()(auto&& lhs, auto&& rhs, auto&& pred = _EXT identity{}) -> _EXT boolean
    {return pred(std::forward<decltype(lhs)>) <= rhs;}
};


struct gt
{
    constexpr auto operator()(auto&& lhs, auto&& rhs, auto&& pred = _EXT identity{}) -> _EXT boolean
    {return pred(std::forward<decltype(lhs)>) > rhs;}
};


struct ge
{
    constexpr auto operator()(auto&& lhs, auto&& rhs, auto&& pred = _EXT identity{}) -> _EXT boolean
    {return pred(std::forward<decltype(lhs)>) >= rhs;}
};


struct eq
{
    constexpr auto operator()(auto&& lhs, auto&& rhs, auto&& pred = _EXT identity{}) -> _EXT boolean
    {return pred(std::forward<decltype(lhs)>) == rhs;}
};


struct ne
{
    constexpr auto operator()(auto&& lhs, auto&& rhs, auto&& pred = _EXT identity{}) -> _EXT boolean
    {return pred(std::forward<decltype(lhs)>) != rhs;}
};
}


// bind arguments to the back of a method, so that when the partial-method is called with arguments, they will the front
// n arguments (using because std::bind_back isn't available yet on MSVC)
template <callable F, typename ...Args0>
struct bind_back
{
public:
    explicit bind_back(F&& function, Args0&&... fixed_args)
            : m_function{std::forward<F>(function)}
            , m_back_args{_EXT make_tuple(std::forward<Args0>(fixed_args)...)}
    {
        // initialize the function and the back arguments, by forwarding the arguments into a tuple and setting this as
        // 'm_back_args'
    }

    template <typename ...Args1>
    constexpr auto operator()(Args1&&... variable_args) const
    {
        // forward the new arguments into a tuple, concatenate this to the front of the 'm_front_args', and apply this
        // tuple to the 'm_function', so that the function is invoked with all the arguments
        return _EXT apply(std::forward<F>(m_function), _EXT tuple_cat(_EXT forward_as_tuple(std::forward<Args1>(variable_args)...), std::move(m_back_args)));
    }

private:
    F&& m_function;
    _EXT tuple<Args0...> m_back_args;
};


template <callable F, typename ...Args0>
bind_back(F&&, Args0&&...) -> bind_back<F, Args0...>;


// bind arguments to the front of a method, so that when the partial-method is called with arguments, they will the back
// n arguments (using because std::bind_back isn't available yet on MSVC, so conform with ext::bind_back)
template <typename F, typename ...Args0>
struct bind_front
{
public:
    explicit bind_front(F&& function, Args0&&... fixed_args)
            : m_function{std::forward<F>(function)}
            , m_front_args{_EXT make_tuple(std::forward<Args0>(fixed_args)...)}
    {
        // initialize the function and the front arguments, by forwarding the arguments into a tuple and setting this as
        // as 'm_front_args'
    };

    template <typename ...Args1>
    constexpr auto operator()(Args1&&... variable_args) const
    {
        // forward the new arguments into a tuple, concatenate this to the back of the 'm_back_args', and apply this
        // tuple to the 'm_function', so that the function is invoked with all the arguments
        return _EXT apply(std::forward<F>(m_function), _EXT tuple_cat(std::move(m_front_args), _EXT forward_as_tuple(std::forward<Args1>(variable_args)...)));
    }

private:
    F&& m_function;
    _EXT tuple<Args0...> m_front_args;
};


template <callable F, typename ...Args0>
bind_front(F&&, Args0&&...) -> bind_front<F, Args0...>;

_EXT_END


#endif //SBROWSER2_FUNCTIONAL_HPP
