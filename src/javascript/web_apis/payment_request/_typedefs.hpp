#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST__TYPEDEFS_HPP

#include "ext/any.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"


namespace payment::detail
{
    enum class state_t {CREATED, INTERACTIVE, CLOSED};
    enum class payment_complete_t {FAIL, SUCCESS, UNKNOWN};

    using payment_method_data_t = ext::map<ext::string, ext::any>;
    using payment_details_update_t = ext::map<ext::string, ext::any>;
    using payment_details_base_t = ext::map<ext::string, ext::any>;
    using payment_details_init_t = ext::map<ext::string, ext::any>;
    using payment_method_init_t = ext::map<ext::string, ext::any>;
    using payment_currency_amount_t = ext::map<ext::string, ext::any>;
    using payment_details_modifier_t = ext::map<ext::string, ext::any>;
    using payment_item_t = ext::map<ext::string, ext::any>;
    using payment_complete_details_t = ext::map<ext::string, ext::any>;
    using payment_validation_errors_t = ext::map<ext::string, ext::any>;

    template <typename T = ext::map<ext::string, ext::any>>
    struct payment_handler_t;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST__TYPEDEFS_HPP
