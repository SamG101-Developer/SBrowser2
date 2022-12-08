#include "rtc_peer_connection.hpp"
#include "rtc_peer_connection_private.hpp"

#include "javascript/environment/settings.ixx"





#include "hr_time/detail/time_internals.hpp"

#include "web_rtc_pc/rtc_certificate.hpp"
#include "web_rtc_pc/rtc_certificate_private.hpp"

#include <range/v3/view/remove_if.hpp>



web_rtc::pc::rtc_peer_connection::rtc_peer_connection(detail::rtc_configuration_t&& configuration)
{
    INIT_PIMPL(rtc_peer_connection);

    JS_EXCEPTION_HANDLER;
    auto e = js::env::env::relevant(this);

    ACCESS_PIMPL(rtc_peer_connection);
    using enum dom::detail::dom_exception_error_t;

    d->document_origin = e.cpp.settings()->origin;
    auto current_time = hr_time::detail::current_hr_time(e.js.global());
    auto original_certificates = configuration[u8"certificates"].to<ext::vector<rtc_certificate*>>();
    auto certificates = original_certificates
            | ranges::views::remove_if([current_time](auto* c) {return c->d_func()->expires < current_time;})
            | ranges::views::remove_if([d](auto* c) {return c->d_func()->origin != d->document_origin;});

    dom::detail::throw_v8_exception<INVALID_ACCESS_ERR>(
            [d, &original_certificates, &certificates] {return original_certificates.size() != certificates.size();},
            u8"Certificate has expired or has an origin mismatch");

    // TODO : If there is an empty certificates list -> create one
    // TODO : Initialzie connections ICE Agent
    detail::set_configuration(this, std::move(configuration));
    d->signaling_state = detail::rtc_signaling_state_t::STABLE;
    d->ice_connection_state = detail::rtc_ice_connection_state_t::NEW;
    d->ice_gathering_state = detail::rtc_ice_gathering_state_t::NEW;
    d->connection_state = detail::rtc_peer_connection_state_t::NEW;
}
