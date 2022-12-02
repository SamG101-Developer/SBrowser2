#include "performance_resource_timing.hpp"
#include "performance_resource_timing_private.hpp"

#include "ext/expected.ixx"

#include "javascript/environment/realms.hpp"

#include "fetch/detail/connection_internals.hpp"
#include "fetch/detail/general_internals.hpp"
#include "hr_time/detail/time_internals.hpp"

#include "server_timing/detail/server_timing_internals.hpp"
#include "server_timing/performance_server_timing.hpp"

#include <range/v3/view/transform.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/to_container.hpp>


auto resource_timing::performance_resource_timing::get_initiator_type() const -> fetch::detail::initiator_type_t
{
    ACCESS_PIMPL(const performance_resource_timing);
    return d->initiator_type;
}


auto resource_timing::performance_resource_timing::get_next_hop_protocol() const -> ext::u8string_view
{
    ACCESS_PIMPL(const performance_resource_timing);
    return d->timing_info->final_connection_timing_info->alpn_negotiated_protocol; // TODO : Check why u8string
}


auto resource_timing::performance_resource_timing::get_worker_start() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL(const performance_resource_timing);
    auto e = js::env::env::relevant(this);
    return hr_time::detail::relative_hr_time(d->timing_info->final_service_worker_start_time, e.js.global());
}


auto resource_timing::performance_resource_timing::get_redirect_start() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL(const performance_resource_timing);
    auto e = js::env::env::relevant(this);
    return hr_time::detail::relative_hr_time(d->timing_info->redirect_start_time, e.js.global());
}


auto resource_timing::performance_resource_timing::get_redirect_end() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL(const performance_resource_timing);
    auto e = js::env::env::relevant(this);
    return hr_time::detail::relative_hr_time(d->timing_info->redirect_end_time, e.js.global());
}


auto resource_timing::performance_resource_timing::get_domain_lookup_start() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL(const performance_resource_timing);
    auto e = js::env::env::relevant(this);
    return hr_time::detail::relative_hr_time(d->timing_info->final_connection_timing_info->domain_lookup_start_time, e.js.global());
}


auto resource_timing::performance_resource_timing::get_domain_lookup_end() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL(const performance_resource_timing);
    auto e = js::env::env::relevant(this);
    return hr_time::detail::relative_hr_time(d->timing_info->final_connection_timing_info->domain_lookup_end_time, e.js.global());
}


auto resource_timing::performance_resource_timing::get_connect_start() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL(const performance_resource_timing);
    auto e = js::env::env::relevant(this);
    return hr_time::detail::relative_hr_time(d->timing_info->final_connection_timing_info->connection_start_time, e.js.global());
}


auto resource_timing::performance_resource_timing::get_connect_end() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL(const performance_resource_timing);
    auto e = js::env::env::relevant(this);
    return hr_time::detail::relative_hr_time(d->timing_info->final_connection_timing_info->connection_end_time, e.js.global());
}


auto resource_timing::performance_resource_timing::get_secure_connection_start() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL(const performance_resource_timing);
    auto e = js::env::env::relevant(this);
    return hr_time::detail::relative_hr_time(d->timing_info->final_connection_timing_info->secure_connection_start_time, e.js.global());
}


auto resource_timing::performance_resource_timing::get_request_start() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL(const performance_resource_timing);
    auto e = js::env::env::relevant(this);
    return hr_time::detail::relative_hr_time(d->timing_info->final_network_request_start_time, e.js.global());
}


auto resource_timing::performance_resource_timing::get_response_start() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL(const performance_resource_timing);
    auto e = js::env::env::relevant(this);
    return hr_time::detail::relative_hr_time(d->timing_info->final_network_response_start_time, e.js.global());
}


auto resource_timing::performance_resource_timing::get_response_end() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL(const performance_resource_timing);
    auto e = js::env::env::relevant(this);
    return hr_time::detail::relative_hr_time(d->timing_info->end_time, e.js.global());
}


auto resource_timing::performance_resource_timing::get_transfer_size() const -> ext::number<ulonglong>
{
    ACCESS_PIMPL(const performance_resource_timing);
    return_if (d->cache_mode == detail::cache_mode_t::LOCAL) 0;
    return_if (d->cache_mode == detail::cache_mode_t::VALIDATED) 300;
    return d->resource_info->encoded_size + 300;
}


auto resource_timing::performance_resource_timing::get_encoded_body_size() const -> ext::number<ulonglong>
{
    ACCESS_PIMPL(const performance_resource_timing);
    return d->resource_info->encoded_size;
}


auto resource_timing::performance_resource_timing::get_decoded_body_size() const -> ext::number<ulonglong>
{
    ACCESS_PIMPL(const performance_resource_timing);
    return d->resource_info->decoded_size;
}


auto resource_timing::performance_resource_timing::get_name() const -> ext::string
{
    ACCESS_PIMPL(const performance_resource_timing);
    return d->requested_url;
}


auto resource_timing::performance_resource_timing::get_start_time() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL(const performance_resource_timing);
    auto e = js::env::env::relevant(this);
    return hr_time::detail::relative_hr_time(d->timing_info->start_time, e.js.global());
}


auto resource_timing::performance_resource_timing::get_duration() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL(const performance_resource_timing);
    return d->timing_info->end_time - d->timing_info->start_time;
}


auto resource_timing::performance_resource_timing::get_server_timing() const -> ext::vector<server_timing::performance_server_timing>
{
    ACCESS_PIMPL(const performance_resource_timing);
    return d->timing_info->server_timing_headers
            | ranges::views::transform(&server_timing::detail::parse_server_timing_header_field)
            | ranges::views::filter(&ext::expected<server_timing::performance_server_timing>::has_value)
            | ranges::views::transform(&ext::expected<server_timing::performance_server_timing>::operator*)
            | ranges::to<ext::vector<server_timing::performance_server_timing>>;
}
