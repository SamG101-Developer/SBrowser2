#ifndef SBROWSER2_RESPONSE_INTERNALS_HPP
#define SBROWSER2_RESPONSE_INTERNALS_HPP

#include <memory>


#include "ext/expected.ixx"
#include "ext/string.hpp"
#include "ext/vector.hpp"

#include INCLUDE_INNER_TYPES(fetch)
#include INCLUDE_INNER_TYPES(url)
#include INCLUDE_INNER_TYPES(service_workers)

namespace fetch {class response;}


namespace fetch::detail
{
    auto serialize_response_url_for_reporting(
            const response_t& response)
            -> ext::string;

    auto is_aborted_network_error(
            const response_t& response)
            -> ext::boolean;

    auto is_network_error(
            const response_t& response)
            -> ext::boolean;

    auto create_appropriate_network_error(
            const fetch_params_t& params)
            -> std::unique_ptr<response_t>;

    auto is_filtered_response(
            const response_t& response)
            -> ext::boolean;

    auto is_basic_filtered_response(
            const response_t& response)
            -> ext::boolean;

    auto is_cors_filtered_response(
            const response_t& response)
            -> ext::boolean;

    auto is_opaque_filtered_response(
            const response_t& response)
            -> ext::boolean;

    auto is_opaque_redirect_filtered_response(
            const response_t& response)
            -> ext::boolean;

    auto clone_response(
            const response_t& response)
            -> std::unique_ptr<response_t>;

    auto is_fresh_response(
            const response_t& response)
            -> ext::boolean;

    auto is_stale_while_revalidate_response(
            const response_t& response)
            -> ext::boolean;

    auto is_stale_response(
            const response_t& response)
            -> ext::boolean;

    auto location_url(
            const response_t& response)
            -> ext::expected<url::detail::url_t>;

    auto create_response_object(
            std::unique_ptr<response_t>&& inner_response,
            header_guard_t header_guard)
            -> std::unique_ptr<response>;

    auto initialize_response_object(
            response* response_object,
            response_init_t&& init,
            body_with_type_t&& body = nullptr)
            -> void;
}


struct fetch::detail::response_t
{
    response_t() = default;
    response_t(const response_t& response);

    response_type_t type = response_type_t::DEFAULT;
    ext::boolean aborted_flag;

    auto associated_url() -> url::detail::url_t;
    ext::vector<url::detail::url_t*> url_list;
    url::detail::url_t* const * url = url_list.end();

    ext::number<ushort> status;
    ext::u8string status_message;

    headers_t header_list;
    ext::variant<ext::u8string, std::shared_ptr<body_t>> body;

    response_cache_t cache_state;
    header_names_t cors_exposed_header_name_list;

    ext::boolean range_requested_flag;
    ext::boolean request_includes_credentials = true;
    ext::boolean timing_allow_passed_flag;

    std::shared_ptr<response_body_info_t> body_information;
    std::shared_ptr<service_workers::detail::service_worker_timing_info_t> service_worker_timing_information;
    ext::boolean has_cross_origin_redirects = false;

    //
    std::unique_ptr<response_t> internal_response;
};


#endif //SBROWSER2_RESPONSE_INTERNALS_HPP
