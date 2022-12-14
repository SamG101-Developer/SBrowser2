module;
#include "ext/macros/namespaces.hpp"
#include <function2/function2.hpp>
#include <tuplet/tuple.hpp>
#include <type_traits>

export module ext.hashing;

import ext.any;
import ext.concepts;
import ext.boolean;
import ext.functional;
import ext.map;
import ext.number;
import ext.set;
import ext.string;
import ext.tuple;
import ext.type_traits;


_EXT_BEGIN
//    struct hash
//    {
//        /*
//         * https://stackoverflow.com/questions/48896142/is-it-possible-to-get-hash-values-as-compile-time-constants
//         * https://stackoverflow.com/a/48896410/10862918
//         * https://stackoverflow.com/users/1896169/justin
//         */
//        template <typename T>
//        constexpr auto operator()(T&& object) const
//        {
//            // For this example, I'm requiring size_t to be 64-bit, but you could
//            // easily change the offset and prime used to the appropriate ones
//            // based on sizeof(size_t).
//            static_assert(sizeof(size_t) == 8);
//            // FNV-1a 64 bit algorithm
//            size_t result = 0xcbf29ce484222325; // FNV offset basis
//
//            for (auto c: object)
//            {
//                result ^= c;
//                result *= 1099511628211; // FNV prime
//            }
//
//            return result;
//        }
//    };


    template <typename Rng>
    auto hash_range(Rng&& range) -> size_t;
_EXT_END


_STD_BEGIN
    export template <>
    struct hash<_EXT any>
    {constexpr auto operator()(const _EXT any& value) const noexcept -> size_t {return *value.m_hash;}};

    export template <>
    struct hash<_EXT boolean>
    {constexpr auto operator()(const _EXT boolean& value) const noexcept -> size_t {return value ? 1 : 0;}};

    export template <typename ...Ts> // TODO
    struct hash<_EXT function<Ts...>>
    {constexpr auto operator()(_EXT function_view<Ts...> value) const noexcept -> size_t {return 0;}};

    export template <typename T>
    struct hash<_EXT number<T>>
    {constexpr auto operator()(const _EXT number<T>& value) const noexcept -> size_t {return _STD hash<T>{}(*value);}};

    export template <_EXT pure_iterable T>
    struct hash<T>
    {constexpr auto operator()(_EXT view_of_t<T> value) const noexcept -> size_t {return _EXT hash_range(value);}};

    export template <typename ...Ts> // TODO
    struct hash<_EXT tuple<Ts...>>
    {constexpr auto operator()(const _EXT tuple<Ts...>& value) const noexcept -> size_t {return 0;}};
_STD_END
