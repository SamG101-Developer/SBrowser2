#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_VIBRATION__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_VIBRATION__TYPEDEFS_HPP

#include "ext/type_traits.ixx"


#include "ext/vector.hpp"

namespace vibration::detail
{
    using vibrate_pattern_t = ext::variant<ext::number<ulong>, ext::vector<ext::number<ulong>>>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_VIBRATION__TYPEDEFS_HPP
