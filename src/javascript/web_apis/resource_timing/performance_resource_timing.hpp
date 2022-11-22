#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_RESOURCE_TIMING_PERFORMANCE_RESOURCE_TIMING_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_RESOURCE_TIMING_PERFORMANCE_RESOURCE_TIMING_HPP

#include "performance_timeline/performance_entry.hpp"
namespace resource_timing {class performance_resource_timing;}
namespace resource_timing {class performance_resource_timing_private;}

#include INCLUDE_INNER_TYPES(fetch)
#include INCLUDE_INNER_TYPES(hr_time)
#include "ext/vector.hpp"
namespace server_timing {class performance_server_timing;}


class resource_timing::performance_resource_timing
        : public performance_timeline::performance_entry
{
public constructors:
    DOM_CTORS(performance_resource_timing);
    MAKE_PIMPL(performance_resource_timing);
    MAKE_V8_AVAILABLE;
    MAKE_STRINGIFIER;

private js_properties:
    /* [RESOURCE-TIMING] */
    DEFINE_GETTER(initiator_type, fetch::detail::initiator_type_t);
    DEFINE_GETTER(next_hop_protocol, ext::u8string_view);
    DEFINE_GETTER(worker_start, hr_time::dom_high_res_time_stamp);
    DEFINE_GETTER(redirect_start, hr_time::dom_high_res_time_stamp);
    DEFINE_GETTER(redirect_end, hr_time::dom_high_res_time_stamp);
    DEFINE_GETTER(fetch_start, hr_time::dom_high_res_time_stamp);
    DEFINE_GETTER(domain_lookup_start, hr_time::dom_high_res_time_stamp);
    DEFINE_GETTER(domain_lookup_end, hr_time::dom_high_res_time_stamp);
    DEFINE_GETTER(connect_start, hr_time::dom_high_res_time_stamp);
    DEFINE_GETTER(connect_end, hr_time::dom_high_res_time_stamp);
    DEFINE_GETTER(secure_connection_start, hr_time::dom_high_res_time_stamp);
    DEFINE_GETTER(request_start, hr_time::dom_high_res_time_stamp);
    DEFINE_GETTER(response_start, hr_time::dom_high_res_time_stamp);
    DEFINE_GETTER(response_end, hr_time::dom_high_res_time_stamp);
    DEFINE_GETTER(transfer_size, ext::number<ulonglong>);
    DEFINE_GETTER(encoded_body_size, ext::number<ulonglong>);
    DEFINE_GETTER(decoded_body_size, ext::number<ulonglong>);

    DEFINE_GETTER(name, ext::string) override;
    DEFINE_GETTER(entry_type, ext::string) override {return u8"resource";}
    DEFINE_GETTER(start_time, hr_time::dom_high_res_time_stamp) override;
    DEFINE_GETTER(duration, hr_time::dom_high_res_time_stamp) override;

    /* [SERVER-TIMING] */
    DEFINE_GETTER(server_timing, ext::vector<server_timing::performance_server_timing>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_RESOURCE_TIMING_PERFORMANCE_RESOURCE_TIMING_HPP
