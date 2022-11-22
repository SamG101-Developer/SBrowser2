#ifndef SBROWSER2_CONNECTION_INTERNALS_HPP
#define SBROWSER2_CONNECTION_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/expected.hpp"
#include "ext/pair.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"

#include INCLUDE_INNER_TYPES(fetch)
#include INCLUDE_INNER_TYPES(hr_time)
#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(url)

namespace js::env {class settings_t;}


namespace fetch::detail
{
    auto origin_caches = ext::map<ext::string, ext::vector<ext::string>>{};

    auto is_ip(
            ext::string_view host)
            -> ext::boolean;

    auto resolve_origin(
            const network_partition_key_t& key,
            const html::detail::origin_t& origin)
            -> ext::expected<ext::vector<ext::string>>;

    auto clamp_and_coarsen_connection_timing_information(
            const connection_timing_info_t& timing_information,
            hr_time::dom_high_res_time_stamp default_start_time,
            ext::boolean cross_origin_isolated_capability)
            -> std::unique_ptr<connection_timing_info_t>;

    auto obtain_connection(
            const network_partition_key_t& key,
            const url::detail::url_t& url,
            ext::boolean credentials,
            new_connection_setting_t new_ = new_connection_setting_t::NO,
            ext::boolean http3_only = false)
            -> ext::expected<std::unique_ptr<connection_t>>;

    auto create_connection(
            const network_partition_key_t& key,
            const html::detail::origin_t& origin,
            ext::boolean credentials,
            ext::string_view proxy,
            ext::string_view host,
            const connection_timing_info_t& timing_info,
            ext::boolean http3_only = false)
            -> ext::expected<std::unique_ptr<connection_t>>;

    auto record_timing_information(
            const connection_t& connection)
            -> void;

    auto determine_network_partition_key(
            js::env::settings_t* environment_settings)
            -> network_partition_key_t;

    auto determine_network_partition_key(
            const request_t& request)
            -> network_partition_key_t;

    auto determine_http_cache_partition(
            const request_t& request)
            -> ext::string;

    auto should_block_due_to_bad_port(
            const request_t& request)
            -> ext::boolean;

    auto should_block_due_to_mime_type(
            const request_t& request)
            -> ext::boolean;
}


struct fetch::detail::connection_timing_info_t
{
    hr_time::dom_high_res_time_stamp domain_lookup_start_time = 0;
    hr_time::dom_high_res_time_stamp domain_lookup_end_time = 0;
    hr_time::dom_high_res_time_stamp connection_start_time = 0;
    hr_time::dom_high_res_time_stamp connection_end_time = 0;
    hr_time::dom_high_res_time_stamp secure_connection_start_time = 0;
    ext::u8string alpn_negotiated_protocol; // TODO : Why us u8string?
};


struct fetch::detail::connection_t
{
    network_partition_key_t key;
    ext::string origin;
    ext::boolean credentials;

    std::unique_ptr<connection_timing_info_t> timing_info;
};


#endif //SBROWSER2_CONNECTION_INTERNALS_HPP
