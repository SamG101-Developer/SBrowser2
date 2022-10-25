#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_RTC_PC_DETAIL_P2P_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_RTC_PC_DETAIL_P2P_INTERNALS_HPP

#include "ext/keywords.hpp"
#include INCLUDE_INNER_TYPES(web_rtc_pc)
namespace web_rtc::pc {class rtc_peer_connection;}


namespace web_rtc::detail
{
    auto chain_operation(
            pc::rtc_peer_connection* connection,
            detail::operation_t& operation)
            -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_RTC_PC_DETAIL_P2P_INTERNALS_HPP
