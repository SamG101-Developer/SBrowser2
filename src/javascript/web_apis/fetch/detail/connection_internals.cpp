#include "connection_internals.hpp"

#include "ext/expected.ixx"

#include "ext/tuple.ixx"




#include "html/_typedefs.hpp"
#include "html/detail/origin_internals.hpp"

#include "fetch/_typedefs.hpp"
#include "fetch/detail/request_internals.hpp"

#include "hr_time/detail/time_internals.hpp"
#include "url/detail/url_internals.hpp"

#include <qhostaddress.h>
#include <qhostinfo.h>
#include <qstring.h>

#include <range/v3/view/transform.hpp>
#include <range/v3/to_container.hpp>


auto fetch::detail::resolve_origin(
        const network_partition_key_t& key,
        const html::detail::origin_t& origin)
        -> ext::expected<ext::vector<ext::string>>
{
    // TODO : Caching

    using namespace ext::literals;
    return_if (is_ip(origin.host)) {origin.host};
    return_if (url::detail::public_suffix(origin.host) == u"localhost") {u"::1", u"127.0.0.1"};

    auto qt_host_info = QHostInfo{};
    qt_host_info.setHostName(origin.host);
    auto qt_addresses = qt_host_info.addresses();
    return qt_host_info.error() == QHostInfo::HostInfoError::NoError ? qt_addresses
            | ranges::views::transform(&QHostAddress::toString)
            | ranges::views::transform(&QString::toStdU16String)
            | ranges::to<ext::vector<ext::string>>()
        : ext::failure_t{};
}


auto fetch::detail::clamp_and_coarsen_connection_timing_information(
        const connection_timing_info_t& timing_information,
        hr_time::dom_high_res_time_stamp default_start_time,
        ext::boolean cross_origin_isolated_capability)
        -> std::unique_ptr<connection_timing_info_t>
{
    auto new_timing_info = std::make_unique<connection_timing_info_t>();
    if (timing_information.connection_start_time < default_start_time)
    {
        new_timing_info->domain_lookup_start_time = timing_information.domain_lookup_start_time;
        new_timing_info->domain_lookup_end_time = timing_information.domain_lookup_end_time;
        new_timing_info->connection_start_time = timing_information.connection_start_time;
        new_timing_info->connection_end_time = timing_information.connection_end_time;
        new_timing_info->secure_connection_start_time = timing_information.secure_connection_start_time;
        new_timing_info->alpn_negotiated_protocol = timing_information.alpn_negotiated_protocol;
        return new_timing_info;
    }

    new_timing_info->domain_lookup_start_time = hr_time::detail::coarsen_time(timing_information.domain_lookup_start_time, cross_origin_isolated_capability);
    new_timing_info->domain_lookup_end_time = hr_time::detail::coarsen_time(timing_information.domain_lookup_end_time, cross_origin_isolated_capability);
    new_timing_info->connection_start_time = hr_time::detail::coarsen_time(timing_information.connection_start_time, cross_origin_isolated_capability);
    new_timing_info->connection_end_time = hr_time::detail::coarsen_time(timing_information.connection_end_time, cross_origin_isolated_capability);
    new_timing_info->secure_connection_start_time = hr_time::detail::coarsen_time(timing_information.connection_end_time, cross_origin_isolated_capability);
    new_timing_info->alpn_negotiated_protocol = timing_information.alpn_negotiated_protocol;
    return new_timing_info;
}


auto fetch::detail::obtain_connection(
        const fetch::detail::network_partition_key_t& key,
        const url::detail::url_t& url,
        ext::boolean credentials,
        fetch::detail::new_connection_setting_t new_,
        ext::boolean http3_only)
        -> ext::expected<std::unique_ptr<connection_t>>
{
    using enum ranges::filter_compare_t;

    if (new_ == new_connection_setting_t::NO)
    {
        auto e = js::env::env::current();
        decltype(auto) connections = js::env::get_slot<connection_pool_t*>(e, js::global_slots::connection_pool);
        decltype(auto) valid_connections = connections
                | ranges::views::filter_eq<EQ>(&connection_t::key, key, ext::identity)
                | ranges::views::filter_eq<EQ>(&connection_t::origin, url::detail::origin(url), ext::identity)
                | ranges::views::filter_eq<EQ>(&connection_t::credentials, credentials, ext::identity);

        return_if (valid_connections.empty() || !http3_only) valid_connections.front();
        // TODO : if there is a http3 connection in connections return it??
    }

    auto proxies = ext::vector<proxy_t>{}; // TODO
    auto timing_info = std::make_unique<connection_timing_info_t>();

    for (decltype(auto) proxy : proxies)
    {
        timing_info->domain_lookup_start_time = hr_time::detail::unsafe_shared_current_time();
        auto hosts = proxy == u"DIRECT" ? ext::vector<ext::string>{url::detail::origin(url).host} : resolve_origin(key, url::detail::origin(url));
        continue_if (!hosts.has_value());
        auto host = (*hosts).front(); // TODO : method to determine best host
        timing_info->domain_lookup_end_time = hr_time::detail::unsafe_shared_current_time();

        // TODO : run n times in parallel
        auto connection = create_connection(key, url::detail::origin(url), credentials, std::move(proxy), std::move(host), *timing_info, http3_only);
        continue_if (!connection.has_value());

        return connection;
    }

    return ext::failure_t{};
}

auto fetch::detail::determine_network_partition_key(
        js::env::settings_t* environment_settings)
        -> network_partition_key_t
{
    decltype(auto) top_level_origin = environment_settings->top_level_origin
            ? *environment_settings->top_level_origin
            : url::detail::origin(*environment_settings->top_level_creation_url);


    // TODO : assertion
    auto top_level_site = html::detail::obtain_site(top_level_origin);
    auto second_key = ext::string{/* TODO */};
    return {top_level_site, second_key};
}


auto fetch::detail::determine_network_partition_key(
        const fetch::detail::request_t& request)
        -> network_partition_key_t
{
    if (!request.reserved_client.IsEmpty())
        return determine_network_partition_key(js::env::get_settings(request.reserved_client));

    if (!request.client.IsEmpty())
        return determine_network_partition_key(js::env::get_settings(request.client));

    return {};
}
