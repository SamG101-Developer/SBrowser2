#ifndef SBROWSER2_CONNECTION_INTERNALS_HPP
#define SBROWSER2_CONNECTION_INTERNALS_HPP


#include "ext/expected.ixx"




#include INCLUDE_INNER_TYPES(fetch)
#include INCLUDE_INNER_TYPES(hr_time)
#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(url)

namespace js::env {class settings_t;}


namespace fetch::detail
{
    auto origin_caches = ext::map<ext::string, ext::vector<ext::string>>{};

    auto is_ip(
            ext::string_view host)
            -> ext::boolean;






}




struct fetch::detail::connection_t
{
    network_partition_key_t key;
    ext::string origin;
    ext::boolean credentials;

    std::unique_ptr<connection_timing_info_t> timing_info;
};


#endif //SBROWSER2_CONNECTION_INTERNALS_HPP
