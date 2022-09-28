#ifndef SBROWSER2_SRC_JAVASCRIPT_INTEROP__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_INTEROP__TYPEDEFS_HPP

#include "ext/number.hpp"
#include "ext/vector.hpp"

namespace javascript::detail::js
{
    using float32_array = ext::vector<ext::number<float >>;
    using float64_array = ext::vector<ext::number<double>>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_INTEROP__TYPEDEFS_HPP
