#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CREDENTIAL_MANAGEMENT__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CREDENTIAL_MANAGEMENT__TYPEDEFS_HPP

#include "ext/any.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"


namespace webappsec::detail
{
    enum class discovery_t {CREDENTIAL_STORE, REMOTE};
    enum class credential_mediation_requirement_t {SILENT, OPTIONAL, CONDITIONAL, REQUIRED};

    struct credential_store_t;

    using credential_creation_options_t = ext::map<ext::string, ext::any>;
    using credential_request_options_t = ext::map<ext::string, ext::any>;
    using credential_data_t = ext::map<ext::string, ext::any>;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CREDENTIAL_MANAGEMENT__TYPEDEFS_HPP
