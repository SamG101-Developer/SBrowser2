#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_METHOD_ID_DETAIL_IDENTIFIER_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_METHOD_ID_DETAIL_IDENTIFIER_INTERNALS_HPP

#include "ext/string.hpp"
#include "ext/boolean.hpp"

#include INCLUDE_INNER_TYPES(url)
#include INCLUDE_INNER_TYPES(payment_method_id)


namespace payment::detail
{
    auto validate_payment_method_identifier(
            payment_method_identifier_t pmi)
            -> ext::boolean;

    auto validate_url_based_payment_method_identifier(
            const url::detail::url_t& url)
            -> ext::boolean;

    auto validate_standardized_payment_method_identifier(
            payment_method_identifier_t string)
            -> ext::boolean;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_METHOD_ID_DETAIL_IDENTIFIER_INTERNALS_HPP
