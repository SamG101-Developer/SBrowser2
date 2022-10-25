#include "rtc_peer_connection.hpp"
#include "environment/environment_settings.hpp"
#include "rtc_peer_connection_private.hpp"


web_rtc::pc::rtc_peer_connection::rtc_peer_connection(detail::rtc_configuration_t&& configuration)
{
    INIT_PIMPL(rtc_peer_connection);
    JS_EXCEPTION_HANDLER;
    JS_REALM_GET_RELEVANT(this);
    decltype(auto) settings_object = v8pp::from_v8<javascript::environment::settings_t*>(this_relevant_agent, this_relevant_settings_object);

    ACCESS_PIMPL(rtc_peer_connection);
    d->document_origin = settings_object->origin;

}
