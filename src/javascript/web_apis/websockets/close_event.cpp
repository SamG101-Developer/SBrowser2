#include "close_event.hpp"
#include "close_event_private.hpp"


websockets::close_event::close_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init)
        : dom::events::event{std::move(event_type), std::move(event_init)}
{
    INIT_PIMPL(close_event);

    ACCESS_PIMPL(close_event);
    d->was_clean = event_init[u"wasClean"].to<decltype(d->was_clean)>();
    d->code = event_init[u"code"].to<decltype(d->code)>();
    d->reason = event_init[u"reason"].to<decltype(d->reason)>();
}
