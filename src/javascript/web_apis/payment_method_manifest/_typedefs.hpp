#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_METHOD_MANIFEST__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_METHOD_MANIFEST__TYPEDEFS_HPP

#include "ext/expected.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"
#include "ext/tuple.hpp"
#include "ext/vector.hpp"
#include INCLUDE_INNER_TYPES(url)
#include INCLUDE_INNER_TYPES(html)

namespace payment::detail
{
    struct parsed_payment_method_manifest_t;

    using manifest_map_t = ext::expected<ext::map<url::detail::url_t*, ext::tuple<url::detail::url_t*, ext::string>>>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_METHOD_MANIFEST__TYPEDEFS_HPP
