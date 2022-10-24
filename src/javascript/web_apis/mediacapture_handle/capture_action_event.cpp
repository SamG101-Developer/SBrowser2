#include "capture_action_event.hpp"
#include "capture_action_event_private.hpp"

#include "mediacapture_main/_typedefs.hpp"


mediacapture::handle::capture_action_event::capture_action_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
{
    INIT_PIMPL(capture_action_event);

    ACCESS_PIMPL(capture_action_event);
    d->action = event_init[u8"action"].to<detail::capture_action_t>();
}


auto mediacapture::handle::capture_action_event::get_action() const -> detail::capture_action_t
{
    ACCESS_PIMPL(const capture_action_event);
    return d->action;
}
