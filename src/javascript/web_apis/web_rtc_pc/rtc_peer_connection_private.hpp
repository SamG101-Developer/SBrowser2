#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_RTC_PC_RTC_PEER_CONNECTION_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_RTC_PC_RTC_PEER_CONNECTION_PRIVATE_HPP

#include "ext/pimpl.ixx"


#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(web_rtc_pc)


DEFINE_PRIVATE_CLASS(web_rtc::pc, rtc_peer_connection) : dom::nodes::event_target_private
{
    detail::rtc_signaling_state_t signaling_state;
    detail::rtc_ice_gathering_state_t ice_gathering_state;
    detail::rtc_ice_connection_state_t ice_connection_state;
    detail::rtc_peer_connection_state_t connection_state;

    // TODO : ICE Agent
    // TODO : Unloading document cleanup steps

    html::detail::origin_t document_origin;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_RTC_PC_RTC_PEER_CONNECTION_PRIVATE_HPP
