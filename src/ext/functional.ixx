export module ext.functional;
import ext.concepts;

#include <compare>
#include <function2/function2.hpp>


_EXT_BEGIN

    export using namespace fu2;

    // Simple functors for parameters (mainly used as range projections)
    export auto identity = []<typename T>(T&& object) {return std::forward<T>(object);};

    export auto negate = []<typename T>(T&& object) {return !std::forward<T>(object);};

    export auto invoke = [](callable auto&& object) {return object();};

    export auto deref = [](auto* object) {return *object;};

    export auto underlying = [](auto&& object) {return object.get();};

    export auto pointer_not_null = [](auto* object) {return object != nullptr;};


    export template <typename ...Ts>
    struct overloaded : Ts...
    {using Ts::operator()...;};

    template <typename ...Ts>
    overloaded(Ts...) -> overloaded<Ts...>;


    namespace cmp
    {
        auto eq = overloaded
                {
            []<typename T, typename U, _EXT callable F>(T&& left, U&& right, F&& proj = _EXT identity) mutable
            {return proj(std::forward<T>(left)) == std::forward<U>(right);},

            []<typename T, typename ...Ts>(T&& left, Ts&&... right)
            {return ((left == std::forward<Ts>(right)) || ...);}
                };

        auto ne = overloaded
                {
            []<typename T, typename U, _EXT callable F>(T&& left, U&& right, F&& proj = _EXT identity) mutable
            {return proj(std::forward<T>(left)) != std::forward<U>(right);},

            []<typename T, typename ...Ts>(T&& left, Ts&&... right)
            {return ((left != std::forward<Ts>(right)) || ...);}
                };

        auto lt = overloaded
                {
            []<typename T, typename U, _EXT callable F>(T&& left, U&& right, F&& proj = _EXT identity) mutable
            {return proj(std::forward<T>(left)) < std::forward<U>(right);},

            []<typename T, typename ...Ts>(T&& left, Ts&&... right)
            {return ((left < std::forward<Ts>(right)) || ...);}
                };

        auto gt = overloaded
                {
            []<typename T, typename U, _EXT callable F>(T&& left, U&& right, F&& proj = _EXT identity) mutable
            {return proj(std::forward<T>(left)) > std::forward<U>(right);},

            []<typename T, typename ...Ts>(T&& left, Ts&&... right)
            {return ((left > std::forward<Ts>(right)) || ...);}
                };

        auto le = overloaded
                {
            []<typename T, typename U, _EXT callable F>(T&& left, U&& right, F&& proj = _EXT identity) mutable
            {return proj(std::forward<T>(left)) <= std::forward<U>(right);},

            []<typename T, typename ...Ts>(T&& left, Ts&&... right)
            {return ((left <= std::forward<Ts>(right)) || ...);}
                };

        auto ge = overloaded
                {
            []<typename T, typename U, _EXT callable F>(T&& left, U&& right, F&& proj = _EXT identity) mutable
            {return proj(std::forward<T>(left)) >= std::forward<U>(right);},

            []<typename T, typename ...Ts>(T&& left, Ts&&... right)
            {return ((left >= std::forward<Ts>(right)) || ...);}
                };
    }


    namespace ops
    {
        auto add =
                []<typename T, typename U>(T&& left, U&& right)
                {return std::forward<T>(left) + std::forward<U>(right);};

        auto minus =
                []<typename T, typename U>(T&& left, U&& right)
                {return std::forward<T>(left) - std::forward<U>(right);};
    }
_EXT_END


#define BIND_NO_ARGS(function)                     \
    []<typename ..._Args>(_Args&&... args) mutable \
    {return function(std::forward<_Args>(args)...);}

#define BIND_FRONT(function, ...)                   \
    [&]<typename ..._Args>(_Args&&... args) mutable \
    {return function(__VA_ARGS__, std::forward<_Args>(args)...);}

#define BIND_BACK(function, ...)                    \
    [&]<typename ..._Args>(_Args&&... args) mutable \
    {return function(std::forward<_Args>(args)..., __VA_ARGS__);}



export template <typename R, typename ...Types>
export auto operator==(const _EXT function<R(Types...)>& lhs, const _EXT function<R(Types...)>& rhs) -> ext::boolean;

export template <typename R, typename ...Types>
export auto operator<=>(const _EXT function<R(Types...)>& lhs, const _EXT function<R(Types...)>& rhs) -> std::strong_ordering;
