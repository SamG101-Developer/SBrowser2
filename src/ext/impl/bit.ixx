module;
#include "ext/macros/namespaces.hpp"


export module ext.core:bit;


_EXT_BEGIN
    export enum class where_t {MOST_SIGNIFICANT, LEAST_SIGNIFICANT};

    export template <typename T, typename U>
    auto set_bits(T& input, U what_to, where_t where);
_EXT_END
