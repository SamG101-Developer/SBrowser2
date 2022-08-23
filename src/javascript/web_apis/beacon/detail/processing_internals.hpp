#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BEACON_DETAIL_PROCESSING_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BEACON_DETAIL_PROCESSING_INTERNALS_HPP

#include "ext/string.hpp"
#include USE_INNER_TYPES(fetch)

namespace beacon::detail
{
    auto send_beacon(
            ext::string_view url,
            fetch::detail::body_init_t options = nullptr)
            -> void;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BEACON_DETAIL_PROCESSING_INTERNALS_HPP
