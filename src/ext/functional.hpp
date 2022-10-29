#ifndef SBROWSER2_FUNCTIONAL_HPP
#define SBROWSER2_FUNCTIONAL_HPP

#include "ext/concepts.hpp"
#include "ext/tuple.hpp"
#include <function2/function2.hpp>


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
            : m_predicate(std::forward<F>(predicate))
    {}

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


namespace cmp
{
    struct eq_fn
    {
        template <typename T, typename U>
        constexpr auto operator()(T&& left, U&& right) const -> _EXT boolean
        {return std::forward<T>(left) == std::forward<U>(right);}
    };

    struct ne_fn
    {
        template <typename T, typename U>
        constexpr auto operator()(T&& left, U&& right) const -> _EXT boolean
        {return std::forward<T>(left) != std::forward<U>(right);}
    };

    eq_fn eq;
    ne_fn ne;
}


#define BIND_FRONT(function, ...)                 \
    [&]<typename ...Args>(Args&&... args) mutable \
    {return function(__VA_ARGS__, std::forward<Args>(args)...);}


#define BIND_BACK(function, ...)                  \
    [&]<typename ...Args>(Args&&... args) mutable \
    {return function(std::forward<Args>(args)..., __VA_ARGS__);}


_EXT_END


template <typename R, typename ...Types> // TODO
auto operator==(const _EXT function<R(Types...)>& lhs, const _EXT function<R(Types...)>& rhs) -> ext::boolean;


//_STD_BEGIN
//    template <typename R, typename ...Types, typename ...Types2>
//    auto construct_at(ext::function<R(Types...)>* const location, Types2...) -> ext::function<R(Types...)>*
//    {}
//_STD_END


#endif //SBROWSER2_FUNCTIONAL_HPP
