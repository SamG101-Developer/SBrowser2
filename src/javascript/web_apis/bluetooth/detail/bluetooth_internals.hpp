#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BLUETOOTH_DETAIL_BLUETOOTH_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BLUETOOTH_DETAIL_BLUETOOTH_INTERNALS_HPP


#include "ext/set.hpp"
#include INCLUDE_INNER_TYPES(bluetooth)


namespace bluetooth::detail
{
    auto bluetooth_device_matches_filter(
            const detail::bluetooth_device_t& device,
            const detail::filter_t& filter)
            -> ext::boolean;
}


struct bluetooth::detail::bluetooth_device_t
{
    ext::set<transport_t> supported_physical_transports;
    char public_bluetooth_address[48];
    char random_static_address[48];
    char private_address[48];

    char identity_resolving_key[128];
    ext::string bluetooth_device_name;

};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BLUETOOTH_DETAIL_BLUETOOTH_INTERNALS_HPP
