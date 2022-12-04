#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MERCHANT_VALIDATION_DETAIL_VALIDATION_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MERCHANT_VALIDATION_DETAIL_VALIDATION_INTERNALS_HPP



#include "ext/promise.ixx"
#include "ext/string.hpp"

namespace payment::request {class payment_request;}


namespace merchant_validation::detail
{
    auto request_merchant_validation(
            ext::string_view merchant_specific_url)
            -> void;

    auto validate_merchant_details(
            ext::promise<ext::any>&& opaque_data_promise,
            payment::request::payment_request* request)
            -> ext::boolean;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MERCHANT_VALIDATION_DETAIL_VALIDATION_INTERNALS_HPP
