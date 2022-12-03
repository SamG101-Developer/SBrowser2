export module ext.bit;

#include "ext/keywords.ixx"


_EXT_BEGIN
    enum class where_t {MOST_SIGNIFICANT, LEAST_SIGNIFICANT};

    template <typename T, typename U>
    auto set_bits(T& input, U what_to, where_t where);
_EXT_END
