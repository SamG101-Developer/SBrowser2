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


#define BIND_FRONT(function, ...)                 \
    [&]<typename ...Args>(Args&&... args) mutable \
    {return function(__VA_ARGS__, std::forward<Args>(args)...);}

#define BIND_BACK(function, ...)                  \
    [&]<typename ...Args>(Args&&... args) mutable \
    {return function(std::forward<Args>(args...), __VA_ARGS__);}


_EXT_END


#endif //SBROWSER2_FUNCTIONAL_HPP
