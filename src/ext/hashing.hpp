#ifndef SBROWSER2_HASHING_HPP
#define SBROWSER2_HASHING_HPP

#include "ext/keywords.hpp"

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

        for (char c : object) {
            result ^= c;
            result *= 1099511628211; // FNV prime
        }

        return result;
    }
};


_EXT_END

#endif //SBROWSER2_HASHING_HPP
