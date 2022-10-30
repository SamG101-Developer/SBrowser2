#ifndef SBROWSER2_FUNCTIONAL_HPP
#define SBROWSER2_FUNCTIONAL_HPP

#include "ext/concepts.hpp"
#include "ext/tuple.hpp"
#include <function2/function2.hpp>


_EXT_BEGIN

using namespace fu2;


auto identity = []<typename T>(T&& object) {return std::forward<T>(object);};

auto negate = []<typename T>(T&& object) {return !std::forward<T>(object);};

auto invoke = [](callable auto&& object) {return object();};

auto deref = [](auto* object) {return *object;};

auto pointer_not_null = [](auto* object) {return object != nullptr;};

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


namespace cmp // TODO : <, >, <=, >=
{
    auto eq =
        []<typename T, typename U>(T&& left, U&& right)
        {return std::forward<T>(left) == std::forward<U>(right);};

    auto ne =
        []<typename T, typename U>(T&& left, U&& right)
        {return std::forward<T>(left) != std::forward<U>(right);};
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


#endif //SBROWSER2_FUNCTIONAL_HPP
