#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_RESOURCE_TIMING_PERFORMANCE_RESOURCE_TIMING_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_RESOURCE_TIMING_PERFORMANCE_RESOURCE_TIMING_HPP

#include "performance_timeline/performance_entry.hpp"
namespace resource_timing {class performance_resource_timing;}

#include INCLUDE_INNER_TYPES(fetch)
#include INCLUDE_INNER_TYPES(hr_time)


class resource_timing::performance_resource_timing
        : public performance_timeline::performance_entry
{
public constructors:
    DOM_CTORS(performance_resource_timing);
    performance_resource_timing() = default;

private js_properties:
    ext::property<ext::string> initiator_type;
    ext::property<ext::string> next_hop_protocol;
    ext::property<hr_time::dom_high_res_time_stamp> worker_start;
    ext::property<hr_time::dom_high_res_time_stamp> redirect_start;
    ext::property<hr_time::dom_high_res_time_stamp> redirect_end;
    ext::property<hr_time::dom_high_res_time_stamp> fetch_start;
    ext::property<hr_time::dom_high_res_time_stamp> domain_lookup_start;
    ext::property<hr_time::dom_high_res_time_stamp> domain_lookup_end;
    ext::property<hr_time::dom_high_res_time_stamp> connect_start;
    ext::property<hr_time::dom_high_res_time_stamp> connect_end;
    ext::property<hr_time::dom_high_res_time_stamp> secure_connection_start;
    ext::property<hr_time::dom_high_res_time_stamp> secure_connection_end;
    ext::property<hr_time::dom_high_res_time_stamp> response_start;
    ext::property<hr_time::dom_high_res_time_stamp> response_end;
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

private js_properties:
    DEFINE_CUSTOM_GETTER(next_hop_protocol);
    DEFINE_CUSTOM_GETTER(worker_start);
    DEFINE_CUSTOM_GETTER(redirect_start);
    DEFINE_CUSTOM_GETTER(redirect_end);
    DEFINE_CUSTOM_GETTER(fetch_start);
    DEFINE_CUSTOM_GETTER(domain_lookup_start);
    DEFINE_CUSTOM_GETTER(domain_lookup_end);
    DEFINE_CUSTOM_GETTER(connect_start);
    DEFINE_CUSTOM_GETTER(connect_end);
    DEFINE_CUSTOM_GETTER(secure_connection_start);
    DEFINE_CUSTOM_GETTER(secure_connection_end);
    DEFINE_CUSTOM_GETTER(response_start);
    DEFINE_CUSTOM_GETTER(response_end);
    DEFINE_CUSTOM_GETTER(transfer_size);
    DEFINE_CUSTOM_GETTER(encoded_body_size);
    DEFINE_CUSTOM_GETTER(decoded_body_size);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_RESOURCE_TIMING_PERFORMANCE_RESOURCE_TIMING_HPP
