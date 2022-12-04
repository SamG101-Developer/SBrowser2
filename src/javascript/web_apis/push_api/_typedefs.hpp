#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API__TYPEDEFS_HPP



#include "ext/string.hpp"


#include <v8-forward.h>

#include INCLUDE_INNER_TYPES(url)
#include INCLUDE_INNER_TYPES(web_idl)


namespace push_api::detail
{
    enum class push_encryption_key_name_t {P256DH, AUTH};

    using push_message_t = ext::string;
    using push_endpoint_t = url::detail::url_t;
    using push_subscription_options_t = ext::map<ext::string, ext::any>;
    using push_subscription_options_init_t = ext::map<ext::string, ext::any>;
    using push_permission_descriptor_t = ext::map<ext::string, ext::any>;
    using push_subscription_json_t = ext::map<ext::string, ext::any>;
    using authentication_secret_t = ext::octet_string;
    using application_server_key_t = ext::variant<ext::variant_monostate_t, ext::string, v8::Local<v8::ArrayBuffer>>;
    using byte_sequence_container_t = ext::variant<ext::string_view, v8::Local<v8::BufferSource>>;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API__TYPEDEFS_HPP
