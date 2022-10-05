#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_METHOD_ID_DETAIL_IDENTIFIER_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_METHOD_ID_DETAIL_IDENTIFIER_INTERNALS_HPP

#include "ext/string.hpp"
#include "ext/boolean.hpp"

#include INCLUDE_INNER_TYPES(url)


namespace payment::detail
{
    auto validate_payment_method_identifier(
            ext::string_view pmi)
            -> ext::boolean;

    auto validate_url_based_payment_method_identifier(
            const url::detail::url_t& url)
            -> ext::boolean;

    auto validate_standardized_payment_method_identifier(
            ext::string_view string)
            -> ext::boolean;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_METHOD_ID_DETAIL_IDENTIFIER_INTERNALS_HPP
