#ifndef SBROWSER2_CONNECTION_INTERNALS_HPP
#define SBROWSER2_CONNECTION_INTERNALS_HPP


#include "ext/string.hpp"
#include "ext/pair.hpp"
#include "ext/boolean.hpp"
#include "ext/map.hpp"

#include USE_INNER_TYPES(fetch)
#include USE_INNER_TYPES(hr_time)
#include USE_INNER_TYPES(url)


namespace fetch::detail
{
    auto resolve_origin(
            const network_partition_key_t&,
            ext::string_view origin)
            -> ext::string;

    auto clamp_and_coarsen_connection_timing_information(
            const connection_timing_info_t& timing_information,
            const hr_time::dom_high_res_time_stamp& default_start_time,
            ext::boolean cross_origin_isolated_capability)
            -> connection_timing_info_t;

    auto obtain_connection(
            const network_partition_key_t& key,
            const url::detail::url_t& url,
            ext::boolean  credentials,
            net_connection_setting_t new_ = net_connection_setting_t::NO,
            ext::boolean  http3_only = false)
            -> connection_t;

    auto create_connection(
            const network_partition_key_t& key,
            ext::string_view origin,
            ext::string_view proxy,
            const connection_timing_info_t& timing_info,
            ext::boolean http3_only = false)
            -> connection_t;

    auto record_timing_information(
            const connection_t& connection)
            -> void;

    auto determine_network_partition_key(
            v8::Local<v8::Object> environment)
            -> network_partition_key_t;

    auto determine_network_partition_key(
            const request_t& request_object)
            -> network_partition_key_t;

    auto determine_http_cache_partition(
            const request_t& request_object)
            -> ext::string;

    auto should_block_due_to_bad_port(
            const request_t& request_obj)
            -> ext::boolean;

    auto should_block_due_to_mime_type(
            const request_t& request_obj)
            -> ext::boolean;
}


struct fetch::detail::connection_t
{
    network_partition_key_t key;
    ext::string origin;
    ext::boolean credentials;

    connection_timing_info_t& timing_info;
};


#endif //SBROWSER2_CONNECTION_INTERNALS_HPP
