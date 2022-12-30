#include <concepts>
module;
#include "ext/macros.hpp"
#include "ext/macros/namespaces.hpp"
#include <cmath>
#include <limits>
#include <utility>


export module ext.core:number;
import :boolean;
import :concepts;
import :random;
import :string;


export using longlong   = long long;
export using uchar      = unsigned char;
export using ushort     = unsigned short;
export using uint       = unsigned int;
export using ulong      = unsigned long;
export using ulonglong  = unsigned long long;
export using longdouble = long double;


#define DEFINE_BINARY_NUMBER_OPERATOR(op)                                                     \
    template <ext::arithmetic T, ext::arithmetic U>                                           \
    constexpr auto operator op (_EXT number<T> lhs, _EXT number<U> rhs) -> _EXT number<T>     \
    {return {*lhs op *rhs};}                                                                  \
                                                                                              \
    template <ext::arithmetic T, ext::arithmetic U>                                           \
    constexpr auto operator op (_EXT number<T> lhs, U rhs) -> _EXT number<T>                  \
    {return {*lhs op rhs};}                                                                   \
                                                                                              \
    template <ext::arithmetic T, ext::arithmetic U>                                           \
    constexpr auto operator op (T lhs, _EXT number<U> rhs) -> T                               \
    {return {lhs op *rhs};}                                                                   \
                                                                                              \
    template <ext::arithmetic T, ext::arithmetic U>                                           \
    constexpr auto operator op##=(_EXT number<T>& lhs, _EXT number<U> rhs) -> _EXT number<T>& \
    {*lhs op##= *rhs; return lhs;}                                                            \
                                                                                              \
    template <ext::arithmetic T, ext::arithmetic U>                                           \
    constexpr auto operator op##=(_EXT number<T>& lhs, U rhs) -> _EXT number<T>&              \
    {*lhs op##= rhs; return lhs;}                                                             \
                                                                                              \
    template <ext::arithmetic T, ext::arithmetic U>                                           \
    constexpr auto operator op##=(T& lhs, _EXT number<U> rhs) -> T&                           \
    {lhs op##= *rhs; return lhs;}


#define DEFINE_BINARY_NUMBER_COMPARISON(op)                                                   \
    template <ext::arithmetic T, ext::arithmetic U>                                           \
    constexpr auto operator op (const ext::number<T>& lhs, const ext::number<U>& rhs) -> bool \
    {return {*lhs op *rhs};}                                                                  \
                                                                                              \
    template <ext::arithmetic T, ext::arithmetic U>                                           \
    constexpr auto operator op (const ext::number<T>& lhs, const U& rhs) -> bool              \
    {return {*lhs op rhs};}                                                                   \
                                                                                              \
    template <ext::arithmetic T, ext::arithmetic U>                                           \
    constexpr auto operator op (const T& lhs, const ext::number<U>& rhs) -> bool              \
    {return {lhs op *rhs};}


_EXT_BEGIN
    // TODO : change boolean to enum (restrict, enforce range, clamp etc)
    export template <arithmetic T, bool unrestricted = false>
    class number;
_EXT_END


_STD_BEGIN
    export template <_STD integral T>
    class numeric_limits<ext::number<T>> : public _Num_int_base
    {
    public:
        _EXT_NODISCARD static constexpr auto (min)() noexcept -> ext::number<T>
        {return std::numeric_limits<T>::min();}

        _EXT_NODISCARD static constexpr auto (max)() noexcept -> ext::number<T>
        {return std::numeric_limits<T>::max();}

        _EXT_NODISCARD static constexpr auto lowest() noexcept -> ext::number<T>
        {return std::numeric_limits<T>::lowest();}

        _EXT_NODISCARD static constexpr auto epsilon() noexcept -> ext::number<T>
        {return std::numeric_limits<T>::epsilon();}

        _EXT_NODISCARD static constexpr auto round_error() noexcept -> ext::number<T>
        {return std::numeric_limits<T>::round_error();}

        _EXT_NODISCARD static constexpr auto denorm_min() noexcept -> ext::number<T>
        {return std::numeric_limits<T>::denorm_min();}

        _EXT_NODISCARD static constexpr auto infinity() noexcept -> ext::number<T>
        {return std::numeric_limits<T>::infinity();}

        _EXT_NODISCARD static constexpr auto quiet_NaN() noexcept -> ext::number<T>
        {return std::numeric_limits<T>::quiet_NaN();}

        _EXT_NODISCARD static constexpr auto signaling_NaN() noexcept -> ext::number<T>
        {return std::numeric_limits<T>::signaling_NaN();}

    static constexpr bool is_modulo = _STD numeric_limits<T>::is_modulo;
    static constexpr int digits     = _STD numeric_limits<T>::digits;
    static constexpr int digits10   = _STD numeric_limits<T>::digits10;
    };

    export template <_STD floating_point T>
    class numeric_limits<ext::number<T>> : public _Num_float_base
    {
        _EXT_NODISCARD static constexpr auto (min)() noexcept -> ext::number<T>
        {return std::numeric_limits<T>::min();}

        _EXT_NODISCARD static constexpr auto (max)() noexcept -> ext::number<T>
        {return std::numeric_limits<T>::max();}

        _EXT_NODISCARD static constexpr auto lowest() noexcept -> ext::number<T>
        {return std::numeric_limits<T>::lowest();}

        _EXT_NODISCARD static constexpr auto epsilon() noexcept -> ext::number<T>
        {return std::numeric_limits<T>::epsilon();}

        _EXT_NODISCARD static constexpr auto round_error() noexcept -> ext::number<T>
        {return std::numeric_limits<T>::round_error();}

        _EXT_NODISCARD static constexpr auto denorm_min() noexcept -> ext::number<T>
        {return std::numeric_limits<T>::denorm_min();}

        _EXT_NODISCARD static constexpr auto infinity() noexcept -> ext::number<T>
        {return std::numeric_limits<T>::infinity();}

        _EXT_NODISCARD static constexpr auto quiet_NaN() noexcept -> ext::number<T>
        {return std::numeric_limits<T>::quiet_NaN();}

        _EXT_NODISCARD static constexpr auto signaling_NaN() noexcept -> ext::number<T>
        {return std::numeric_limits<T>::signaling_NaN();}

        static constexpr int digits         = _STD numeric_limits<T>::digits;
        static constexpr int digits10       = _STD numeric_limits<T>::digits10;
        static constexpr int max_digits10   = _STD numeric_limits<T>::max_digits10;
        static constexpr int max_exponent   = _STD numeric_limits<T>::max_exponent;
        static constexpr int max_exponent10 = _STD numeric_limits<T>::max_exponent10;
        static constexpr int min_exponent   = _STD numeric_limits<T>::min_exponent;
        static constexpr int min_exponent10 = _STD numeric_limits<T>::min_exponent10;
    };
_STD_END


_EXT_BEGIN
    export template <bool IncludeLo, bool IncludeHi, typename T, typename U, typename V>
    auto is_between(T&& value, U&& lo, V&& hi) -> boolean
    {
        auto condition1 = IncludeLo ? value >= lo : value > lo; // default to >
        auto condition2 = IncludeHi ? value <= hi : value < hi; // default to <
        return condition1 && condition2;
    }


    export template <typename T, typename U, typename ...V>
    auto min(T&& value0, U&& value1, V&&... values)
    {
        if constexpr(sizeof...(values) == 0) return value0 < value1 ? value0 : value1;
        else return min(min(std::forward<T>(value0), std::forward<U>(value1)), std::forward<V>(values)...);
    }


    export template <typename T, typename U, typename ...V>
    auto max(T&& value0, U&& value1, V&&... values)
    {
        if constexpr(sizeof...(values) == 0) return value0 > value1 ? value0 : value1;
        else return max(max(std::forward<T>(value0), std::forward<U>(value1)), std::forward<V>(values)...);
    }


    export template <typename T, typename U>
    auto round(T&& value, U&& multiplier)
    {return std::round(*ext::number{std::move(value / multiplier)}) * std::forward<U>(multiplier);}


    export template <typename T>
    auto absolute(T&& value)
    {return value < 0 ? -value : value;}


    export template <_EXT string_view_like S>
    auto is_numeric_string(S string) -> boolean;


    export template <_EXT string_like S = ext::string, typename T>
    auto to_string(number<T> number) -> S
    {/* TODO */}


    export template <typename ...Args>
    auto is_inf(Args&&... numbers)
    {return ((numbers == std::numeric_limits<std::remove_reference_t<Args>>::infinity()) || ...);}


    export template <typename ...Args>
    auto is_nan(Args&&... numbers)
    {return ((numbers == std::numeric_limits<std::remove_reference_t<Args>>::quiet_NaN()) || ...);}


    export template <typename ...Args>
    auto is_inf_or_nan(Args&&... numbers)
    {return is_inf(std::forward<Args>(numbers)...) || is_nan(std::forward<Args>(numbers)...);}


    export template <typename T>
    auto abs(T number) -> T
    {return number * ((number > 0) - (number < 0));}
_EXT_END


template <_EXT arithmetic T, bool unrestricted>
class ext::number final
{
public:
    template <_EXT arithmetic U, bool>
    friend class _EXT number;

    using value_t = T;

    constexpr number(T val): n(val) {}
    constexpr number() = default;
    number(const number&) = default;
    number(number&&) noexcept = default;
    auto operator=(const number&) -> number& = default;
    auto operator=(number&&) noexcept -> number& = default;

    template <_EXT string_like S>
    static auto from_string(S&& string) -> number;

    template <_EXT string_view_like S>
    static auto from_string(S&& string_view) -> number;

    auto operator=(T val) -> number&
    {n = val; return *this;}

    auto operator++() -> number&
    {++n; return *this;}

    auto operator--() -> number&
    {--n; return *this;}

    auto operator-() -> number&
    {n *= -1; return *this;}

    template <_EXT arithmetic U>
    auto operator=(const ext::number<U>& val)
    {n = *val;}

    template <_EXT arithmetic U>
    operator number<U>() const
    {return {static_cast<U>(n)};}

    constexpr auto operator*() -> T& {return n;}
    constexpr auto operator*() const -> const T& {return n;}
    constexpr operator bool() const {return n != 0;}

    template <_EXT arithmetic U>
    auto as() const {return ext::number<U>{static_cast<U>(n)};}

    static auto inf() -> number
    {return std::numeric_limits<T>::infinity();}

    static auto nan() -> number
    {return std::numeric_limits<T>::quiet_NaN();}

    static auto min() -> number
    {return std::numeric_limits<T>::min();}

    static auto max() -> number
    {return std::numeric_limits<T>::max();}

    template <typename U, typename V>
    static auto random(U&& minimum = ext::number<T>::min(), V&& maximum = ext::number<T>::max()) -> number
    {return ext::random::get(std::forward<U>(minimum), std::forward<V>(maximum));}

private:
    T n;
};


_EXT_LITERALS_BEGIN
    export auto operator""_n(char number) {return _EXT number<char>{number};}
    export auto operator""_n(ulonglong number) {return _EXT number<ulonglong>{number};}
    export auto operator""_n(longdouble number) {return _EXT number<longdouble>{number};}
_EXT_LITERALS_END


DEFINE_BINARY_NUMBER_OPERATOR(+)
DEFINE_BINARY_NUMBER_OPERATOR(-)
DEFINE_BINARY_NUMBER_OPERATOR(*)
DEFINE_BINARY_NUMBER_OPERATOR(/)
DEFINE_BINARY_NUMBER_OPERATOR(%)
DEFINE_BINARY_NUMBER_OPERATOR(&)
DEFINE_BINARY_NUMBER_OPERATOR(|)
DEFINE_BINARY_NUMBER_OPERATOR(^)
DEFINE_BINARY_NUMBER_OPERATOR(<<)
DEFINE_BINARY_NUMBER_OPERATOR(>>)

DEFINE_BINARY_NUMBER_COMPARISON(<)
DEFINE_BINARY_NUMBER_COMPARISON(<=)
DEFINE_BINARY_NUMBER_COMPARISON(>)
DEFINE_BINARY_NUMBER_COMPARISON(>=)
DEFINE_BINARY_NUMBER_COMPARISON(==)
DEFINE_BINARY_NUMBER_COMPARISON(!=)
