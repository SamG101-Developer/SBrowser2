#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_CRYPTO__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_CRYPTO__TYPEDEFS_HPP


#include "ext/map.ixx"
#include "ext/string.hpp"



namespace web_crypto::detail
{
    enum class key_type_t {PUBLIC, PRIVATE, SECRET};
    enum class key_usage_t {ENCRYPT, DECRYPT, SIGN, VERIFY, DERIVE_KEY, DERIVE_BITS, WRAP_KEY, UNWRAP_KEY};
    enum class key_format_t {RAW, PKCS8, SPKI, JWK};

    using algorithm_identifier_t = ext::variant<void*, ext::string>;
    using hash_algorithm_identifier_t = algorithm_identifier_t;
    using algorithm_t = ext::map<ext::string, ext::any>;
    using key_algorithm_t = ext::map<ext::string, ext::any>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_CRYPTO__TYPEDEFS_HPP
