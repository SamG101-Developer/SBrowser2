#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API__TYPEDEFS_HPP

#include "ext/any.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"
#include "ext/variant.hpp"

#include <v8-forward.h>

#include INCLUDE_INNER_TYPES(url)


namespace push_api::detail
{
    using push_message_t = ext::string;
    using push_endpoint_t = url::detail::url_t;
    using push_subscription_options_t = ext::map<ext::string, ext::any>;
    using push_subscription_options_init_t = ext::map<ext::string, ext::any>;
    using push_permission_descriptor_t = ext::map<ext::string, ext::any>;
    using push_subscription_json_t = ext::map<ext::string, ext::any>;
    using authentication_secret_t = ext::octet_string;
    using application_server_key_t = ext::variant<ext::variant_monostate_t, ext::string, v8::Local<v8::ArrayBuffer>>;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API__TYPEDEFS_HPP
