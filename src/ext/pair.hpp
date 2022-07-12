#ifndef SBROWSER2_PAIR_HPP
#define SBROWSER2_PAIR_HPP

#include <tuple>

namespace ext {struct pair_name_equal_to_fn;}
namespace ext {struct pair_value_equal_to_fn;}


struct ext::pair_name_equal_to_fn
{
    template <typename K, typename V>
    constexpr auto operator()(std::pair<K, V>&& _Pair, V&& _ValCompare)
    {
        return _Pair.first == std::forward<V>(_ValCompare);
    }
};


struct ext::pair_value_equal_to_fn
{
    template <typename K, typename V>
    constexpr auto operator()(std::pair<K, V>&& _Pair, V&& _ValCompare)
    {
        return _Pair.second == std::forward<V>(_ValCompare);
    }
};


namespace ext {constexpr pair_name_equal_to_fn pair_name_equal_to;}
namespace ext {constexpr pair_value_equal_to_fn pair_value_equal_to_fn;}


#endif //SBROWSER2_PAIR_HPP
