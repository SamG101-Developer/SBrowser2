#include "response_internals.hpp"

#include "ext/assertion.hpp"
#include "ext/ranges.hpp"

#include "fetch/_typedefs.hpp"
#include "fetch/detail/body_internals.hpp"
#include "fetch/detail/general_internals.hpp"
#include "fetch/detail/header_internals.hpp"

#include "url/detail/url_internals.hpp"

#include <range/v3/algorithm/all_of.hpp>
#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/set_algorithm.hpp>


fetch::detail::response_t::response_t(const response_t& response)
{
    type = response.type;
    aborted_flag = response.aborted_flag;
    url_list = response.url_list;
    status = response.status;
    status_message = response.status_message;
    header_list = response.header_list;
    body = response.body;
    cache_state = response.cache_state;
    cors_exposed_header_name_list = response.cors_exposed_header_name_list;
    range_requested_flag = response.range_requested_flag;
    request_includes_credentials = response.request_includes_credentials;
    timing_allow_passed_flag = response.timing_allow_passed_flag;
    body_information = response.body_information;
    service_worker_timing_information = response.service_worker_timing_information;
    has_cross_origin_redirects = response.has_cross_origin_redirects;
    internal_response = nullptr;
}


auto fetch::detail::is_aborted_network_error(
        const response_t& response)
        -> ext::boolean
{
    return is_network_error(response) && response.aborted_flag;
}


auto fetch::detail::is_network_error(
        const response_t& response)
        -> ext::boolean
{
    return response.type == response_type_t::ERROR
            && response.status == 0
            && response.status_message.empty()
            && response.header_list.empty()
            && !response.body;
}


auto fetch::detail::create_appropriate_network_error(
        const fetch_params_t& params)
        -> std::unique_ptr<response_t>
{
    ASSERT(is_cancelled(params));
    auto aborted_network_error = std::make_unique<response_t>();
    aborted_network_error->type = response_type_t::ERROR;
    aborted_network_error->aborted_flag = true;
    return std::move(aborted_network_error);
}


auto fetch::detail::is_filtered_response(
        const response_t& response)
        -> ext::boolean
{
    return response.internal_response
            && !is_network_error(*response.internal_response);
}


auto fetch::detail::is_basic_filtered_response(
        const response_t& response)
        -> ext::boolean
{
    decltype(auto) internal_forbidden_response_headers = response.internal_response->header_list | ranges::views::filter(is_forbidden_header_name);
    decltype(auto) response_forbidden_response_headers = ranges::views::set_intersection(response.header_list, std::move(internal_forbidden_response_headers));

    return is_filtered_response(response)
            && response.type == response_type_t::BASIC
            && response_forbidden_response_headers.empty();
}


auto fetch::detail::is_cors_filtered_response(
        const response_t& response)
        -> ext::boolean
{
    decltype(auto) internal_cors_unsafe_headers = response.internal_response->cors_exposed_header_name_list | ranges::views::filter(ext::negate_function{is_cors_safelisted_response_header_name});
    decltype(auto) response_cors_unsafe_headers = ranges::views::set_intersection(response.header_list, std::move(internal_cors_unsafe_headers));

    return is_filtered_response(response)
            && response.type == response_type_t::CORS
            && response_cors_unsafe_headers.empty();
}


auto fetch::detail::is_opaque_filtered_response(
        const response_t& response)
        -> ext::boolean
{
    return is_filtered_response(response)
            && response.type == response_type_t::OPAQUE
            && response.url_list.empty()
            && response.status == 0
            && response.status_message.empty()
            && response.header_list.empty()
            && response.body == nullptr;
}


auto fetch::detail::is_opaque_redirect_filtered_response(
        const response_t& response)
        -> ext::boolean
{
    return is_filtered_response(response)
            && response.type == response_type_t::OPAQUE_REDIRECT
            && response.status == 0
            && response.status_message.empty()
            && response.header_list.empty()
            && response.body == nullptr;
}


auto fetch::detail::clone_response(
        const response_t& response)
        -> std::unique_ptr<response_t>
{
    auto new_response = std::make_unique<response_t>(response);

    if (is_filtered_response(response))
        new_response->internal_response = clone_response(*response.internal_response);
    else
        new_response->body = clone_body(*response.body);

    return new_response;
}


auto fetch::detail::is_fresh_response(
        const fetch::detail::response_t& response)
        -> ext::boolean
{
    auto current_age = ext::number<double>{get_header_value(u"Age"    , response.header_list)};
    auto max_age     = ext::number<double>{get_header_value(u"Max-Age", response.header_list)};
    return current_age < max_age;
}


auto fetch::detail::is_stale_while_revalidate_response(
        const fetch::detail::response_t& response)
        -> ext::boolean
{
    auto current_age = ext::number<double>{get_header_value(u"Age"    , response.header_list)};
    auto stale_lifetime = ext::number<double>{get_header_value(u"Stale-While-Revalidate", response.header_list)};
    return is_fresh_response(response) && current_age < stale_lifetime;
}


auto fetch::detail::is_stale_response(
        const fetch::detail::response_t& response)
        -> ext::boolean
{
    return !is_fresh_response(response);
}


auto fetch::detail::location_url(
        const fetch::detail::response_t& response)
        -> ext::expected<url::detail::url_t>
{
    return_if (!ranges::contains(redirect_status, response.status)) url::detail::url_t{u""};
    auto location = extract_header_list_values(u"Location", response.header_list);
    // TODO
}
