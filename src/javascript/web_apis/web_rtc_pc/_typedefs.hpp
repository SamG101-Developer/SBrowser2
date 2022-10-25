#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_RTC_PC__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_RTC_PC__TYPEDEFS_HPP

#include "ext/any.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"


namespace web_rtc::detail
{
    enum class rtc_ice_trtansport_policy {RELAY, ALL};
    enum class rtc_bundle_policy_t {BALANCED, MAX_COMPAT, MAX_BUNDLE};
    enum class rtc_rtcp_mux_policy_t {REQUIRE};
    enum class rtc_signaling_state_t {STABLE, HAVE_LOCAL_OFFER, HAVE_REMOTE_OFFSET, HAVE_LOCAL_PRANSWER, HAVE_REMOTE_PRANSWER, CLOSED};
    enum class rtc_ice_gathering_state_t {NEW, GATHERING, COMPLETE};
    enum class rtc_peer_connection_state_t {CLOSED, FAILED, DISCONNECTED, NEW, CONNECTING, CONNECTED};
    enum class rtc_ice_connection_state_t {CLOSED, FAILED, DISCONNECTED, NEW, CHECKING, cOMPLETED, CONNECTED};

    using rtc_configuration_t = ext::map<ext::string, ext::any>;
    using rtc_ice_server_t = ext::map<ext::string, ext::any>;
    using rtc_offer_answer_options = ext::map<ext::string, ext::any>;
    using rtc_offset_options = rtc_offer_answer_options;
    using rtc_answer_options = rtc_offer_answer_options;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_RTC_PC__TYPEDEFS_HPP
