#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER__TYPEDEFS_HPP

#include "ext/any.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"


namespace payment::detail
{
    using payment_instrument_t = ext::map<ext::string, ext::any>;
    using image_object_t = ext::map<ext::string, ext::any>;
    using payment_request_details_update_t = ext::map<ext::string, ext::any>;
    using payment_handler_reponse_t = ext::map<ext::string, ext::any>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER__TYPEDEFS_HPP
