#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_NETWORK_ERROR_LOGGING__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_NETWORK_ERROR_LOGGING__TYPEDEFS_HPP

#include "ext/string.hpp"


namespace network_error_logging::detail
{
    struct nel_policy_t;
    struct report_body_t;
    struct network_error_report_t;
    struct network_error_t;

    // TODO : maybe some more enums for dns/tls errors

    using network_error_type_t = ext::string;
    enum class network_error_phase_t {DNS, CONNECTION, APPLICATION};
    enum class network_request_phase_t {DNS_RESOLUTION, SECURE_CONNECTION_ESTABLISHMENT, TRANSMISSION_OF_REQUEST_AND_RESPONSE};

}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_NETWORK_ERROR_LOGGING__TYPEDEFS_HPP
