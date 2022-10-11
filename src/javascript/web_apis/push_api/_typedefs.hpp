#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API__TYPEDEFS_HPP

#include "ext/any.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"

#include "ext/set.hpp"
#include "ext/vector.hpp"

#include INCLUDE_INNER_TYPES(url)


namespace push_api::detail
{
    using push_message_t = ext::string;
    using push_endpoint_t = url::detail::url_t;
    using push_subscription_options_init_t = ext::map<ext::string, ext::any>;
    using authentication_secret_t = ext::octet_string;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API__TYPEDEFS_HPP
