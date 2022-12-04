#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_RTC_PC_RTC_PEER_CONNECTION_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_RTC_PC_RTC_PEER_CONNECTION_HPP

// Inheritance Includes & This Class
#include "dom/nodes/event_target.hpp"
namespace web_rtc::pc {class rtc_peer_connection;}
namespace web_rtc::pc {class rtc_peer_connection_private;}

// Other Includes & Forward Declarations
#include INCLUDE_INNER_TYPES(web_rtc_pc)



class web_rtc::pc::rtc_peer_connection
        : public dom::nodes::event_target
{
public constructors:
    rtc_peer_connection(detail::rtc_configuration_t&& configuration = {});
    MAKE_PIMPL(rtc_peer_connection);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto create_offer(detail::rtc_offer_options&& options = {}) -> ext::promise<detail::rtc_session_description_init_t>;
    auto create_answer(detail::rtc_answer_options&& options = {}) -> ext::promise<detail::rtc_session_description_init_t>;
    auto set_local_description(detail::rtc_local_session_description_init_t&& = {}) -> ext::promise<void>;
    auto set_remote_description(detail::rtc_session_description_init_t&& = {}) -> ext::promise<void>;
    auto add_ice_candidate(detail::rtc_ice_candidate_init_t&& candidate = {}) -> ext::promise<void>;

    auto restart_ice() -> void;
    auto get_configuration() -> detail::rtc_configuration_t;
    auto set_configuration(detail::rtc_configuration_t&& configuration = {}) -> void;
    auto close() -> void;

public js_properties:
    DEFINE_GETTER(local_description, detail::rtc_session_description_t);
    DEFINE_GETTER(current_local_description, detail::rtc_session_description_t);
    DEFINE_GETTER(pending_local_description, detail::rtc_session_description_t);

    DEFINE_GETTER(remote_description, detail::rtc_session_description_t);
    DEFINE_GETTER(current_remote_description, detail::rtc_session_description_t);
    DEFINE_GETTER(pending_remote_description, detail::rtc_session_description_t);

    DEFINE_GETTER(signaling_state, detail::rtc_signaling_state_t);
    DEFINE_GETTER(ice_gathering_state, detail::rtc_ice_gathering_state_t);
    DEFINE_GETTER(ice_connection_state, detail::rtc_ice_connection_state_t);
    DEFINE_GETTER(connection_state, detail::rtc_peer_connection_state_t);
    DEFINE_GETTER(can_trickle_ice_candidates, ext::boolean);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_RTC_PC_RTC_PEER_CONNECTION_HPP
