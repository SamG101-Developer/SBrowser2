#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_METHOD_CREDIT_TRANSFER__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_METHOD_CREDIT_TRANSFER__TYPEDEFS_HPP

#include "ext/any.hpp"
#include "ext/map.ixx"
#include "ext/string.hpp"


namespace payment::detail
{
    using credit_transfer_request_t = ext::map<ext::string, ext::any>;
    using credit_transfer_response_t = ext::map<ext::string, ext::any>;
    using payee_credit_transfer_response_t = ext::map<ext::string, ext::any>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_METHOD_CREDIT_TRANSFER__TYPEDEFS_HPP
