#ifndef SBROWSER2_CONNECTION_INTERNALS_HPP
#define SBROWSER2_CONNECTION_INTERNALS_HPP


#include "ext/string.hpp"
#include "ext/pair.hpp"
#include "ext/boolean.hpp"
#include "ext/map.hpp"

#include "../_typedefs.hpp"
#include "high_resolution_time/_typedefs.hpp"
#include "url/url.hpp"
namespace fetch::detail::http_internals {struct connection_timing_info;}
namespace fetch::detail::request_internals {struct internal_request;}

namespace fetch::detail
{
    auto resolve_origin(
            const network_partition_key_t&,
            ext::string_view origin)
            -> ext::string;

    auto clamp_and_coarsen_connection_timing_information(
            http_internals::connection_timing_info& timing_information,
            high_resolution_time::dom_high_res_time_stamp_t default_start_time,
            ext::boolean cross_origin_isolated_capability)
            -> http_internals::connection_timing_info;

    auto obtain_connection(
            const network_partition_key_t& key,
            const url::url_object& url,
            const ext::boolean& credentials,
            net_connection_setting_t new_ = net_connection_setting_t::NO,
            const ext::boolean& http3_only = false)
            -> connection_t;

    auto create_connection(
            const network_partition_key_t& key,
            ext::string_view origin,
            ext::string_view proxy,
            http_internals::connection_timing_info& timing_info,
            const ext::boolean& http3_only = false)
            -> connection_t;

    auto record_timing_information(
            const connection_t& connection)
            -> void;

    auto determine_network_partition_key(
            v8::Local<v8::Object> environment)
            -> network_partition_key_t;

    auto determine_network_partition_key(
            request_internals::internal_request& request_object)
            -> network_partition_key_t;

    auto determine_http_cache_partition(
            request_internals::internal_request& request_object)
            -> ext::string;

    auto should_block_due_to_bad_port(
            request_internals::internal_request& request_obj)
            -> ext::boolean;

    auto should_block_due_to_mime_type(
            request_internals::internal_request& request_obj)
            -> ext::boolean;
}


struct fetch::detail::connection_t
{
    network_partition_key_t key;
    ext::string origin;
    ext::boolean credentials;

    http_internals::connection_timing_info& timing_info;
};


#endif //SBROWSER2_CONNECTION_INTERNALS_HPP
