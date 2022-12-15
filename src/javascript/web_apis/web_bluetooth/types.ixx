export module apis.web_bluetooth.types;

import ext.any;
import ext.boolean;
import ext.map;
import ext.string;


export namespace web_bluetooth::detail
{
    struct bluetooth_cache_t;
    struct bluetooth_device_t;
}


struct web_bluetooth::detail::bluetooth_device_t
{
    using bluetooth_le_scan_filter_init_t = ext::map<ext::string, ext::any>;

    auto matches_filter(bluetooth_le_scan_filter_init_t&& filter) -> ext::boolean;
};
