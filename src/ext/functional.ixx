module;
#include "ext/macros/namespaces.hpp"
#include <function2/function2.hpp>
#include <utility>


export module ext.functional;
import ext.boolean;
import ext.concepts;

_EXT_BEGIN
    export using namespace ::fu2;
_EXT_END

_EXT_BEGIN
    export template <_EXT callable F>
    constexpr auto bind_no_args(F&& function)
    {
        return [function = std::forward<F>(function)]<typename ...Args>(Args&&... args) mutable
        {return function(std::forward<Args>(args)...);};
    }

    export template <_EXT callable F, typename ...FArgs>
    constexpr auto bind_front(F&& function, FArgs&&... f_args)
    {
        return [function = std::forward<F>(function), ...f_args = std::forward<FArgs>(f_args)]<typename ...BArgs>(BArgs&&... b_args) mutable
        {return function(std::forward<FArgs>(f_args)..., std::forward<BArgs>(b_args)...);};
    }

    export template <_EXT callable F, typename ...BArgs>
    constexpr auto bind_back(F&& function, BArgs&&... b_args)
    {
        return [function = std::forward<F>(function), ...b_args = std::forward<BArgs>(b_args)]<typename ...FArgs>(FArgs&&... f_args) mutable
        {return function(std::forward<FArgs>(f_args)..., std::forward<BArgs>(b_args)...);};
    }

    // Simple functors for parameters (mainly used as range projections)
    export auto identity = []<typename T>(T&& object) {return std::forward<T>(object);};
    export auto negate = []<typename T>(T&& object) {return !std::forward<T>(object);};
    export auto invoke = [](_EXT callable auto&& object) {return object();};
    export auto deref = [](auto* object) {return *object;};
    export auto underlying = [](auto&& object) {return object.get();};
    export auto pointer_not_null = [](auto* object) {return object != nullptr;};
    export auto get_pimpl = []<_EXT has_pimpl T>(T* object) {return object->d_func();};

    export template <typename ...Ts>
    struct overloaded : Ts...
    {using Ts::operator()...;};

    template <typename ...Ts>
    overloaded(Ts...) -> overloaded<Ts...>;

    export template <_EXT callable F>
    struct inverse_function;

    export namespace cmp
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


    export namespace ops
    {
        auto add =
                []<typename T, typename U>(T&& lhs, U&& rhs)
                {return std::forward<T>(lhs) + std::forward<U>(rhs);};

        auto sub =
                []<typename T, typename U>(T&& lhs, U&& rhs)
                {return std::forward<T>(lhs) - std::forward<U>(rhs);};

        auto mul =
                []<typename T, typename U>(T&& lhs, U&& rhs)
                {return std::forward<T>(lhs) * std::forward<U>(lhs);};

        auto div =
                []<typename T, typename U>(T&& lhs, U&& rhs)
                {return std::forward<T>(lhs) / std::forward<U>(rhs)};

        auto and_ =
                []<typename T, typename U>(T&& lhs, U&& rhs)
                {return std::forward<T>(lhs) && std::forward<U>(rhs);};
    }
_EXT_END


export template <_EXT callable F>
struct _EXT inverse_function final
{
public:
    explicit inverse_function(F&& function)
    {m_function = std::forward<F>(function);}

    template <typename ...Args>
    constexpr auto operator()(Args&&...args) const
    {return !m_function(std::forward<Args>(args)...);}

private:
    F m_function;
};


export template <typename ...Ts>
auto operator==(const _EXT function<Ts...>& lhs, const _EXT function<Ts...>& rhs) -> ext::boolean;

export template <typename R, typename ...Ts>
auto operator<=>(const _EXT function<Ts...>& lhs, const _EXT function<Ts...>& rhs) -> std::strong_ordering;
