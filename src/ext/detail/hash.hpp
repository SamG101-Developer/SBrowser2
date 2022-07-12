#ifndef SBROWSER2_HASH_HPP
#define SBROWSER2_HASH_HPP


namespace ext {constexpr auto hash(const char* str) -> size_t;}

constexpr auto ext::hash(const char* str) -> size_t {
    const long long p = 131;
    const long long m = 4294967291; // 2^32 - 5, largest 32 bit prime
    long long total = 0;
    long long current_multiplier = 1;
    for (int i = 0; str[i] != '\0'; ++i)
    {
        total = (total + current_multiplier * str[i]) % m;
        current_multiplier = (current_multiplier * p) % m;
    }
    return total;
}


#endif //SBROWSER2_HASH_HPP
