#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_RESOURCE_TIMING_PERFORMANCE_RESOURCE_TIMING_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_RESOURCE_TIMING_PERFORMANCE_RESOURCE_TIMING_HPP

#include "performance_timeline/performance_entry.hpp"
namespace resource_timing {class performance_resource_timing;}

#include USE_INNER_TYPES(fetch)
#include USE_INNER_TYPES(high_resolution_time)


class resource_timing::performance_resource_timing
        : public performance_timeline::performance_entry
{
public constructors:
    DOM_CTORS(performance_resource_timing);
    performance_resource_timing() = default;

public js_properties:
    ext::property<ext::string> initiator_type;
    ext::property<ext::string> next_hop_protocol;
    ext::property<high_resolution_time::detail::dom_high_res_time_stamp_t> worker_start;
    ext::property<high_resolution_time::detail::dom_high_res_time_stamp_t> redirect_start;
    ext::property<high_resolution_time::detail::dom_high_res_time_stamp_t> redirect_end;
    ext::property<high_resolution_time::detail::dom_high_res_time_stamp_t> fetch_start;
    ext::property<high_resolution_time::detail::dom_high_res_time_stamp_t> domain_lookup_start;
    ext::property<high_resolution_time::detail::dom_high_res_time_stamp_t> domain_lookup_end;
    ext::property<high_resolution_time::detail::dom_high_res_time_stamp_t> connect_start;
    ext::property<high_resolution_time::detail::dom_high_res_time_stamp_t> connect_end;
    ext::property<high_resolution_time::detail::dom_high_res_time_stamp_t> secure_connection_start;
    ext::property<high_resolution_time::detail::dom_high_res_time_stamp_t> secure_connection_end;
    ext::property<high_resolution_time::detail::dom_high_res_time_stamp_t> response_start;
    ext::property<high_resolution_time::detail::dom_high_res_time_stamp_t> response_end;
    ext::property<ext::number<ulonglong>> transfer_size;
    ext::property<ext::number<ulonglong>> encoded_body_size;
    ext::property<ext::number<ulonglong>> decoded_body_size;

public cpp_methods:
    auto to_json() const -> ext::string override;

private cpp_properties:
    ext::string m_initiator_type;
    ext::string m_requested_url;
    ext::string m_cache_mode;
    std::unique_ptr<fetch::detail::fetch_timing_info_t> timing_info;
    std::unique_ptr<fetch::detail::response_body_info_t> response_body_info;

private cpp_accessors:
    DEFINE_GETTER(next_hop_protocol);
    DEFINE_GETTER(worker_start);
    DEFINE_GETTER(redirect_start);
    DEFINE_GETTER(redirect_end);
    DEFINE_GETTER(fetch_start);
    DEFINE_GETTER(domain_lookup_start);
    DEFINE_GETTER(domain_lookup_end);
    DEFINE_GETTER(connect_start);
    DEFINE_GETTER(connect_end);
    DEFINE_GETTER(secure_connection_start);
    DEFINE_GETTER(secure_connection_end);
    DEFINE_GETTER(response_start);
    DEFINE_GETTER(response_end);
    DEFINE_GETTER(transfer_size);
    DEFINE_GETTER(encoded_body_size);
    DEFINE_GETTER(decoded_body_size);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_RESOURCE_TIMING_PERFORMANCE_RESOURCE_TIMING_HPP
