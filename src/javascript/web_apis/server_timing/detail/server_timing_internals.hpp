#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVER_TIMING_DETAIL_SERVER_TIMING_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVER_TIMING_DETAIL_SERVER_TIMING_INTERNALS_HPP

#include "ext/expected.hpp"
#include "ext/string.hpp"
namespace server_timing {class performance_server_timing;}


namespace server_timing::detail
{
    auto parse_server_timing_header_field(
            ext::string field)
            -> ext::expected<performance_server_timing>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVER_TIMING_DETAIL_SERVER_TIMING_INTERNALS_HPP
