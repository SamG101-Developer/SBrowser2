#ifndef SBROWSER2_HASHING_HPP
#define SBROWSER2_HASHING_HPP

#include "ext/any.hpp"
#include "ext/boolean.hpp"
#include "ext/functional.hpp"
#include "ext/map.hpp"
#include "ext/number.hpp"
#include "ext/set.hpp"
#include "ext/tuple.hpp"
#include <type_traits>


_EXT_BEGIN

struct hash
{
    /*
     * https://stackoverflow.com/questions/48896142/is-it-possible-to-get-hash-values-as-compile-time-constants
     * https://stackoverflow.com/a/48896410/10862918
     * https://stackoverflow.com/users/1896169/justin
     */
    template <typename T>
    constexpr auto operator()(T&& object) const
    {
        // For this example, I'm requiring size_t to be 64-bit, but you could
        // easily change the offset and prime used to the appropriate ones
        // based on sizeof(size_t).
        static_assert(sizeof(size_t) == 8);
        // FNV-1a 64 bit algorithm
        size_t result = 0xcbf29ce484222325; // FNV offset basis

        for (char c: object) {
            result ^= c;
            result *= 1099511628211; // FNV prime
        }

        return result;
    }
};

_EXT_END


_STD_BEGIN
    template <>
    struct hash<_EXT any>
    {constexpr auto operator()(const _EXT any& value) const noexcept -> size_t {return *value.m_hash;}};

    template <>
    struct hash<_EXT boolean>
    {constexpr auto operator()(const _EXT boolean& value) const noexcept -> size_t {return value ? 1 : 0;}};

    template <typename ...Ts>
    struct hash<_EXT function<Ts...>>
    {constexpr auto operator()(const _EXT function<Ts...>& value) const noexcept -> size_t {return _STD hash<size_t>{}(static_cast<size_t>(&value));}};

    template <typename K, typename V>
    struct hash<_EXT map<K, V>>
    {constexpr auto operator()(const _EXT map<K, V>& value) const noexcept -> size_t {return _STD hash<size_t>{}(&value);}};

    template <typename T>
    struct hash<_EXT number<T>>
    {constexpr auto operator()(const _EXT number<T>& value) const noexcept -> size_t {return _STD hash<T>{}(*value);}};

    template <typename T>
    struct hash<_EXT set<T>>
    {constexpr auto operator()(const _EXT set<T>& value) const noexcept -> size_t {return _STD hash<size_t>{}(&value);}};

    template <typename ...Ts>
    struct hash<_EXT tuple<Ts...>>
    {constexpr auto operator()(const _EXT tuple<Ts...>& value) const noexcept -> size_t {return 0;}};
_STD_END


#endif //SBROWSER2_HASHING_HPP
