#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BLUETOOTH__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BLUETOOTH__TYPEDEFS_HPP





namespace bluetooth::detail
{
    struct bluetooth_cache_t;
    struct bluetooth_device_t;
    struct filter_t;

    enum class transport_t;

    using bluetooth_data_filter_init_t = ext::map<ext::string, ext::any>;
    using bluetooth_manufacture_data_filter_init_t = ext::map<ext::string, ext::any>;
    using bluetooth_service_data_filter_init_t = ext::map<ext::string, ext::any>;
    using bluetooth_le_scan_filter_init_t = ext::map<ext::string, ext::any>;
    using request_device_options_t = ext::map<ext::string, ext::any>;
    using address_t = ext::string;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BLUETOOTH__TYPEDEFS_HPP
