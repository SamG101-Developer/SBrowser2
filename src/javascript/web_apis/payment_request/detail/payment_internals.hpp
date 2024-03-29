#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_DETAIL_PAYMENT_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_DETAIL_PAYMENT_INTERNALS_HPP



#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(payment_request)

namespace payment::request {class payment_request;}


namespace payment::detail
{
    auto payment_relevant_browsing_context(
            request::payment_request* request)
            -> html::detail::browsing_context_t&;

    auto is_valid_decimal_monetary_value(
            ext::string_view string)
            -> ext::boolean;

    auto check_and_canonicalize_amount(
            detail::payment_currency_amount_t& amount)
            -> void;

    auto check_and_canonicalize_total_amount(
            detail::payment_currency_amount_t& amount)
            -> void;

    auto can_make_payment_algorithm(
            request::payment_request* request)
            -> void;

    auto payment_method_changed_algorithm(
            request::payment_request* request)
            -> void;

    auto payment_method_updated_algorithm(
            request::payment_request* request)
            -> void;

    auto user_accepts_payment_request_algorithm(
            request::payment_request* request)
            -> void;

    auto user_aborts_payment_request_algorithm(
            request::payment_request* request)
            -> void;

    auto update_payment_requests_details_algorithm(
            ext::promise<detail::payment_details_update_t>& details_promise,
            request::payment_request* request)
            -> void;

    auto abort_update(
            request::payment_request* request)
            -> void;
};


template <typename T>
struct payment::detail::payment_handler_t
{
    using data_type_t = T;

    ext::function<void()> validate_payment_data;
    ext::function<void()> check_if_payment_can_be_made;
    ext::function<void()> response_to_payment_method_data;
    ext::function<void()> user_changes_payment_method;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_DETAIL_PAYMENT_INTERNALS_HPP
