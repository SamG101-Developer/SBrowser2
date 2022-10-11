#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API__TYPEDEFS_HPP

#include "ext/string.hpp"

#include INCLUDE_INNER_TYPES(url)


namespace push_api::detail
{
    using push_message_t = ext::string;
    using push_endpoint_t = url::detail::url_t;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API__TYPEDEFS_HPP
