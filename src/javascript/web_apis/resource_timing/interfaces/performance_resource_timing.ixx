module;
#include "ext/macros.hpp"


export module apis.resource_timing.performance_resource_timing;
import apis.performance_timeline.performance_entry;

IMPORT_ALL_TYPES(fetch);
IMPORT_ALL_TYPES(hr_time);
IMPORT_ALL_TYPES(server_timing);


DEFINE_PUBLIC_CLASS(resource_timing, performance_resource_timing)
        : public performance_timeline::performance_entry
{
public constructors:
    MAKE_PIMPL(performance_resource_timing);
    MAKE_V8_AVAILABLE(WINDOW | WORKER);
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

    DEFINE_GETTER(name, ext::string_view) override;
    DEFINE_GETTER(entry_type, ext::string_view) override;
    DEFINE_GETTER(start_time, hr_time::dom_high_res_time_stamp) override;
    DEFINE_GETTER(duration, hr_time::dom_high_res_time_stamp) override;

    /* [SERVER-TIMING] */
    DEFINE_GETTER(server_timing, ext::vector<server_timing::performance_server_timing>);
};
